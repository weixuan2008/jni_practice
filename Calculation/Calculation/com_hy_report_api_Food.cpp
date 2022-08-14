#include "com_hy_report_api_Food.h"
#include <stdlib.h>
#include "Food.h"
#include <string.h>

char* jstring2string(JNIEnv* env, jstring jstr)
{
	char* rtn = NULL;
	jclass clsstring = env->FindClass("java/lang/String");
	jstring strencode = env->NewStringUTF("utf-8");
	jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
	jbyteArray barr = (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
	jsize alen = env->GetArrayLength(barr);
	jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);

	if (alen > 0)
	{
		rtn = (char*)malloc(alen + 1);

		memcpy(rtn, ba, alen);
		rtn[alen] = 0;
	}
	env->ReleaseByteArrayElements(barr, ba, 0);
	return rtn;
}

jstring char2Jstring(JNIEnv* env, const char* pat)
{
	jclass strClass = env->FindClass("Ljava/lang/String;");
	jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
	jbyteArray bytes = env->NewByteArray(strlen(pat));
	env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);
	jstring encoding = env->NewStringUTF("utf-8");
	return (jstring)env->NewObject(strClass, ctorID, bytes, encoding);
}

CFood* getCFood(JNIEnv* env, jobject thiz)
{
	jclass clazz = env->GetObjectClass(thiz);
	jfieldID fid = env->GetFieldID(clazz, "mObject", "J");
	jlong p = env->GetLongField(thiz, fid);
	return (CFood*)p;
}

void setFood(JNIEnv* env, jobject thiz, const CFood* pFood)
{
	jclass clazz = env->GetObjectClass(thiz);
	jfieldID fid = env->GetFieldID(clazz, "mObject", "J");
	env->SetLongField(thiz, fid, (jlong)pFood);
}

JNIEXPORT void JNICALL Java_com_hy_report_api_Food_setFoodParam
(JNIEnv* env, jobject thiz, jstring name, jdouble price)
{
	//const char* tempName = env->GetStringUTFChars(name, 0);
	char* tempName = jstring2string(env, name);
	double tempPrice = price;

	CFood* pFood = new CFood(tempName, tempPrice);
	setFood(env, thiz, pFood);
}

JNIEXPORT jstring JNICALL Java_com_hy_report_api_Food_getName
(JNIEnv* env, jobject thiz)
{
	CFood* pFood = getCFood(env, thiz);
	const char* name = pFood->getName();
	return char2Jstring(env, name);
}

JNIEXPORT jdouble JNICALL Java_com_hy_report_api_Food_getPrice
(JNIEnv* env, jobject thiz)
{
	CFood* pFood = getCFood(env, thiz);
	return pFood->getPrice();
}

JNIEXPORT void JNICALL Java_com_hy_report_api_Food_finalize
(JNIEnv* env, jobject thiz)
{
	CFood* pFood = getCFood(env, thiz);
	if (pFood != NULL)
	{
		delete pFood;
		pFood = NULL;
		setFood(env, thiz, pFood);
	}
}