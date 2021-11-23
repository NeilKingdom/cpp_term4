#include <math.h>
#include "Week8_JNIDemo.h"

JNIEXPORT jdouble JNICALL Java_Week8_JNIDemo_calculateSTDDev(JNIEnv* env, jobject obj, jintArray randomValues, jdouble mean) {

    double sum = 0;
    jint lenOfRandValues = env->GetArrayLength(randomValues);
    jint* values = env->GetIntArrayElements(randomValues, NULL);

    for(int i = 0; i < lenOfRandValues; i++)
        sum += pow(((double)values[i] - mean), 2);

    env->ReleaseIntArrayElements(randomValues, values, 0);
    return (sqrt(sum/lenOfRandValues));
}

JNIEXPORT jdouble JNICALL Java_Week8_JNIDemo_calculateMean(JNIEnv* env, jobject obj, jintArray randomValues) {

    double sum = 0;
    jint lenOfRandValues = env->GetArrayLength(randomValues);
    jint* values = env->GetIntArrayElements(randomValues, NULL);

    for(int i = 0; i < lenOfRandValues; i++)
        sum += values[i];

    env->ReleaseIntArrayElements(randomValues, values, 0);
    return (sum/lenOfRandValues);
}