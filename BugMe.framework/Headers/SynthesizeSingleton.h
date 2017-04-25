//
//  SynthesizeSingleton.h
//
//  Created by Charanjit Singh on 17/10/16.
//  Copyright © 2016 Charanjit Singh. All rights reserved.

#ifndef SYNTHESIZE_SINGLETON_FOR_CLASS

#import <objc/runtime.h>


#pragma mark -
#pragma mark Singleton

#define SYNTHESIZE_SINGLETON_FOR_CLASS_HEADER(__CLASSNAME__)	\
	\
+ (__CLASSNAME__*) sharedInstance;	\
+ (void) purgeSharedInstance;


#define SYNTHESIZE_SINGLETON_FOR_CLASS(__CLASSNAME__)	\
	\
static volatile __CLASSNAME__* _##__CLASSNAME__##_sharedInstance = nil;	\
	\
+ (__CLASSNAME__*) sharedInstanceNoSynch	\
{	\
	return (__CLASSNAME__*) _##__CLASSNAME__##_sharedInstance;	\
}	\
	\
+ (__CLASSNAME__*) sharedInstanceSynch	\
{	\
	@synchronized(self)	\
	{	\
		if(nil == _##__CLASSNAME__##_sharedInstance)	\
		{	\
			_##__CLASSNAME__##_sharedInstance = [[self alloc] init];	\
		}	\
		else	\
		{	\
			NSAssert2(1==0, @"SynthesizeSingleton: %@ ERROR: +(%@ *)sharedInstance method did not get swizzled.", self, self);	\
		}	\
	}	\
	return (__CLASSNAME__*) _##__CLASSNAME__##_sharedInstance;	\
}	\
	\
+ (__CLASSNAME__*) sharedInstance	\
{	\
	return [self sharedInstanceSynch]; \
}	\
	\
+ (id)allocWithZone:(NSZone*) zone	\
{	\
	@synchronized(self)	\
	{	\
		if (nil == _##__CLASSNAME__##_sharedInstance)	\
		{	\
			_##__CLASSNAME__##_sharedInstance = [super allocWithZone:zone];	\
			if(nil != _##__CLASSNAME__##_sharedInstance)	\
			{	\
				Method newSharedInstanceMethod = class_getClassMethod(self, @selector(sharedInstanceNoSynch));	\
				method_setImplementation(class_getClassMethod(self, @selector(sharedInstance)), method_getImplementation(newSharedInstanceMethod));	\
			}	\
		}	\
	}	\
	return (__CLASSNAME__*) _##__CLASSNAME__##_sharedInstance;	\
}	\
	\
+ (void)purgeSharedInstance	\
{	\
	@synchronized(self)	\
	{	\
		if(nil != _##__CLASSNAME__##_sharedInstance)	\
		{	\
			Method newSharedInstanceMethod = class_getClassMethod(self, @selector(sharedInstanceSynch));	\
			method_setImplementation(class_getClassMethod(self, @selector(sharedInstance)), method_getImplementation(newSharedInstanceMethod));	\
			_##__CLASSNAME__##_sharedInstance = nil;	\
		}	\
	}	\
}	\
	\
- (id)copyWithZone:(NSZone *)zone	\
{	\
	return self;	\
}
#pragma mark -
#pragma mark Lesser Singleton

/* A lesser singleton has a shared instance, but can also be instantiated on its own.
 *
 * For a lesser singleton, you still use SYNTHESIZE_SINGLETON_FOR_CLASS_HEADER(),
 * but use SYNTHESIZE_LESSER_SINGLETON_FOR_CLASS() in the implementation file.
 * You must specify which creation methods are to initialize the shared instance
 * (besides "sharedInstance") via CALL_LESSER_SINGLETON_INIT_METHOD()
 *
 * Example:
 *
 * MyClass.h:
 * ========================================
 *	#import "SynthesizeSingleton.h"
 *
 *	@interface MyClass: SomeSuperclass
 *	{
 *		int value;
 *		...
 *	}
 *	SYNTHESIZE_SINGLETON_FOR_CLASS_HEADER(MyClass);
 *
 *	+ (void) initSharedInstanceWithValue:(int) value;
 *
 * - (id) initWithValue:(int) value;
 *
 *	@end
 * ========================================
 *
 *
 *	MyClass.m:
 * ========================================
 *	#import "MyClass.h"
 *
 *	@implementation MyClass
 *
 *	SYNTHESIZE_LESSER_SINGLETON_FOR_CLASS(MyClass);
 *
 *	+ (void) initSharedInstanceWithValue:(int) value
 *	{
 *		CALL_LESSER_SINGLETON_INIT_METHOD(MyClass, initWithValue:value);
 *	}
 *
 *	...
 *
 *	@end
 * ========================================
 *
 *
 * Note: CALL_LESSER_SINGLETON_INIT_METHOD() will not work if your
 * init call contains commas.  If you need commas (such as for varargs),
 * or other more complex initialization, use the PRE and POST macros:
 *
 *	+ (void) initSharedInstanceComplex
 *	{
 *		CALL_LESSER_SINGLETON_INIT_METHOD_PRE(MyClass);
 *
 *		int firstNumber = [self getFirstNumberSomehow];
 *		_sharedInstance = [[self alloc] initWithValues:firstNumber, 2, 3, 4, -1];
 *
 *		CALL_LESSER_SINGLETON_INIT_METHOD_POST(MyClass);
 *	}
 */

#define SYNTHESIZE_LESSER_SINGLETON_FOR_CLASS(__CLASSNAME__)	\
	\
static volatile __CLASSNAME__* _##__CLASSNAME__##_sharedInstance = nil;	\
	\
+ (__CLASSNAME__*) sharedInstanceNoSynch	\
{	\
	return (__CLASSNAME__*) _##__CLASSNAME__##_sharedInstance;	\
}	\
	\
+ (__CLASSNAME__*) sharedInstanceSynch	\
{	\
	@synchronized(self)	\
	{	\
		if(nil == _##__CLASSNAME__##_sharedInstance)	\
		{	\
			_##__CLASSNAME__##_sharedInstance = [[self alloc] init];	\
			if(_##__CLASSNAME__##_sharedInstance)	\
			{	\
				Method newSharedInstanceMethod = class_getClassMethod(self, @selector(sharedInstanceNoSynch));	\
				method_setImplementation(class_getClassMethod(self, @selector(sharedInstance)), method_getImplementation(newSharedInstanceMethod));	\
			}	\
		}	\
		else	\
		{	\
			NSAssert2(1==0, @"SynthesizeSingleton: %@ ERROR: +(%@ *)sharedInstance method did not get swizzled.", self, self);	\
		}	\
	}	\
	return (__CLASSNAME__*) _##__CLASSNAME__##_sharedInstance;	\
}	\
	\
+ (__CLASSNAME__*) sharedInstance	\
{	\
	return [self sharedInstanceSynch]; \
}	\
	\
+ (void)purgeSharedInstance	\
{	\
	@synchronized(self)	\
	{	\
		Method newSharedInstanceMethod = class_getClassMethod(self, @selector(sharedInstanceSynch));	\
		method_setImplementation(class_getClassMethod(self, @selector(sharedInstance)), method_getImplementation(newSharedInstanceMethod));	\
			\
		_##__CLASSNAME__##_sharedInstance = nil;	\
	}	\
}


#define CALL_LESSER_SINGLETON_INIT_METHOD_PRE(__CLASSNAME__) \
	@synchronized(self)	\
	{	\
		if(nil == _##__CLASSNAME__##_sharedInstance)	\
		{


#define CALL_LESSER_SINGLETON_INIT_METHOD_POST(__CLASSNAME__) \
			if(_##__CLASSNAME__##_sharedInstance)	\
			{	\
				Method newSharedInstanceMethod = class_getClassMethod(self, @selector(sharedInstanceNoSynch));	\
				method_setImplementation(class_getClassMethod(self, @selector(sharedInstance)), method_getImplementation(newSharedInstanceMethod));	\
			}	\
		}	\
		else	\
		{	\
			NSAssert1(1==0, @"SynthesizeSingleton: %@ ERROR: _sharedInstance has already been initialized.", self);	\
		}	\
	}


#define CALL_LESSER_SINGLETON_INIT_METHOD(__CLASSNAME__,__INIT_CALL__) \
	CALL_LESSER_SINGLETON_INIT_METHOD_PRE(__CLASSNAME__); \
	_##__CLASSNAME__##_sharedInstance = [[self alloc] __INIT_CALL__];	\
	CALL_LESSER_SINGLETON_INIT_METHOD_POST(__CLASSNAME__)

#endif /* SYNTHESIZE_SINGLETON_FOR_CLASS */
