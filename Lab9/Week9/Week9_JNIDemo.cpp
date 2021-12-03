#include <math.h>
#include <omp.h>
#include <iostream>
#include "Week9_JNIDemo.h"

JNIEXPORT jdouble JNICALL Java_Week9_JNIDemo_calculateSTDDev(JNIEnv* env, jobject obj, jintArray randomValues, jdouble mean) {

    jint lenOfRandValues = env->GetArrayLength(randomValues);
    jint* values = env->GetIntArrayElements(randomValues, NULL);
    double sum = 0;

    #pragma omp parallel for reduction(+: sum)
        for(int i = 0; i < lenOfRandValues; i++)
            sum += pow(((double)values[i] - mean), 2);

    double res = sqrt(sum/lenOfRandValues);
    env->ReleaseIntArrayElements(randomValues, values, 0);
    return res;
}

JNIEXPORT jdouble JNICALL Java_Week9_JNIDemo_calculateMean(JNIEnv* env, jobject obj, jintArray randomValues) {

    #pragma omp parallel
    {
        int numThreads = omp_get_num_threads();
        #pragma omp single
        std::cout << "You have " << numThreads << " processor(s)" << std::endl;
    }

    double sum = 0;
    jint lenOfRandValues = env->GetArrayLength(randomValues);
    jint* values = env->GetIntArrayElements(randomValues, NULL);

    #pragma omp parallel for reduction(+: sum)
        for(int i = 0; i < lenOfRandValues; i++)
            sum += values[i];

    double res = (sum/lenOfRandValues);
    env->ReleaseIntArrayElements(randomValues, values, 0);
    return res;
}