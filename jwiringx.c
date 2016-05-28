/*
 * MIT License
 * 
 * Copyright (c) 2016 Josua Mayer <josua.mayer97@gmail.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// generated JNI declerations
#include "jwiringx.h"

// logconsumer implementation
#include "jlogconsumer.h"

// the real wiringX
#include <wiringX.h>

// limits for converting numeric types
#include <limits.h>

// variadics
#include <stdarg.h>

// helper functions
jobject create(JNIEnv *env, const char *classpath) {
    jobject result;

    // look-up class
    jclass class = (*env)->FindClass(env, classpath);
    if(class == NULL)
        return NULL;

    // look-up constructor
    jmethodID cid = (*env)->GetMethodID(env, class, "<init>", "()V");
    if(cid == NULL)
        return NULL;

    // create object
    result = (*env)->NewObject(env, class, cid);

    // free local resources
    (*env)->DeleteLocalRef(env, class);

    // done
    return result;
}

void throw_new_exception(JNIEnv *env, const char *classname, const char *message) {
    jclass class = (*env)->FindClass(env, classname);
    if(class == NULL) {
        // classnotfound
        // exception already thrown
        return;
    }

    // throw it
    (*env)->ThrowNew(env, class, message);
}

void Java_wiringX_delayMicroseconds(JNIEnv *env, jclass c, jlong delay) {
    // check arguments for valid value-range (unsigned int)
    if(delay < 0 || delay > UINT_MAX) {
        // lookup exception class
        jclass illegalargumentexceptionclass = (*env)->FindClass(env, "java/lang/IllegalArgumentException");
        if(illegalargumentexceptionclass == NULL)
            return;

        // throw it
        (*env)->ThrowNew(env, illegalargumentexceptionclass, "Value out of Range");
        // TODO: check return-value

        // free exception class reference
        (*env)->DeleteLocalRef(env, illegalargumentexceptionclass);
        
        // return to java
        return;
    }

    // call original function
    delayMicroseconds((int)delay);
}

jint Java_wiringX_pinMode(JNIEnv *env, jclass c, jint pin, jobject mode) {
    // look-up PinMode class
    jclass class = (*env)->FindClass(env, "PinMode");
    if(class == NULL) {
        // exception was thrown, return to java
        return 0;
    }

    // check type
    if(!(*env)->IsInstanceOf(env, mode, class)) {
        // type mismatch, throw exception
        throw_new_exception(env, "java/lang/ClassCastException", "Not an instance of PinMode");\
        return 0;
    }

    // get ordinal method
    jmethodID mid = (*env)->GetMethodID(env, class, "ordinal", "()I");
    if(mid == NULL) {
        // methodnotfound
        // exception already thrown
        return 0;
    }

    // get ordinal value
    jint ordinal = (*env)->CallIntMethod(env, mode, mid);
    if((*env)->ExceptionCheck(env)) {
        // an exception occured
        return 0;
    }

    // convert to C enum
    // Java Ordinals start from 0 and go to N in order of declaration
    enum pinmode_t modec;
    switch(ordinal) {
        case 0: modec = PINMODE_NOT_SET; break;
        case 1: modec = PINMODE_INPUT; break;
        case 2: modec = PINMODE_OUTPUT; break;
        case 3: modec = PINMODE_INTERRUPT; break;
        default:
            // not good, throw an exception
            throw_new_exception(env, "java/lang/EnumConstantNotPresentException", "");
            return 0;
    }

    // call original function
    return (jint)pinMode((int)pin, modec);
}

jint Java_wiringX_Setup(JNIEnv *env, jclass c, jstring platform, jobject logger) {
    // create UTF-8 encoded C-string from given platform string
    const char *platformc = (*env)->GetStringUTFChars(env, platform, NULL);
    if(platformc == NULL) {
        // allocating a C-String failed!
        // at this point an exception should have already been thrown.
        // The return value is now irrelevant.
        return 0;
    }

    // register logger, if any
    void *handler = NULL;
    if(logger != NULL) {
        int r = registerLogConsumer(env, logger);
        if(r != 0) {
            // unexpected failure
            // exceptions have already been thrown
            return -1;
        }

        // looks good
        handler = &logconsumerhandler;
    }

    // call original function
    int r = wiringXSetup((char *)platformc, handler);

    // free resources
    (*env)->ReleaseStringUTFChars(env, platform, platformc);
    
    // return result
    return r;
}

void Java_wiringX_GC(JNIEnv *env, jclass c) {
    wiringXGC();
}

jint Java_wiringX_digitalWrite(JNIEnv *env, jclass c, jint pin, jobject value) {
    // look-up DigitalValue class
    jclass class = (*env)->FindClass(env, "DigitalValue");
    if(class == NULL) {
        // exception was thrown, return to java
        return 0;
    }

    // check type
    if(!(*env)->IsInstanceOf(env, value, class)) {
        // type mismatch, throw exception
        throw_new_exception(env, "java/lang/ClassCastException", "Not an instance of DigitalValue");\
        return 0;
    }

    // get ordinal method
    jmethodID mid = (*env)->GetMethodID(env, class, "ordinal", "()I");
    if(mid == NULL) {
        // methodnotfound
        // exception already thrown
        return 0;
    }

    // get ordinal value
    jint ordinal = (*env)->CallIntMethod(env, value, mid);
    if((*env)->ExceptionCheck(env)) {
        // an exception occured
        return 0;
    }

    // convert to C enum
    // Java Ordinals start from 0 and go to N in order of declaration
    enum digital_value_t valuec;
    switch(ordinal) {
        case 0: valuec = LOW; break;
        case 1: valuec = HIGH; break;
        default:
            // not good, throw an exception
            throw_new_exception(env, "java/lang/EnumConstantNotPresentException", "");
            return 0;
    }

    // call original function
    return (jint)digitalWrite((int)pin, valuec);
}

jint Java_wiringX_digitalRead(JNIEnv *env, jclass c, jint pin) {
    return (jint)digitalRead((int)pin);
}

jint Java_wiringX_waitForInterrupt(JNIEnv *env, jclass c, jint pin, jint timeout) {
    return (jint)waitForInterrupt((int)pin, (int)timeout);
}
