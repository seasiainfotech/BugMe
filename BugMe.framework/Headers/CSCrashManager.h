//
//  CSCrashManager.h
//  BugMe
//
//  Created by Charanjit Singh on 17/10/16.
//  Copyright © 2016 Charanjit Singh. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SynthesizeSingleton.h"

@interface CSCrashManager : NSObject
{
    /** The full path to the error report that this manager will write to. */
    NSString* errorReportPath;
    /** The delegate to inform when a crash occurs (can be nil). */
    id delegate;
    /** The selector to call on the delegate. */
    SEL callbackSelector;
}

SYNTHESIZE_SINGLETON_FOR_CLASS_HEADER(CSCrashManager);
/**
 * Start managing crashes.
 */
- (void) manageCrashes;

/**
 * Stop managing crashes.
 */
- (void) stopManagingCrashes;

/** The error report's path.
 * Note: If you set this to a value that doesn't start with "/", it will
 *       be expanded to a full path relative to the Documents directory.
 */
@property(readwrite,nonatomic,retain) NSString* errorReportPath;

/** The error report.  If there is no report, this will be nil. */
@property(readonly,nonatomic) NSString* errorReport;

/** If true, there is an error report present. */
@property(readonly,nonatomic) bool errorReportPresent;

/**
 * Delete the error report (if any).
 */
- (void) deleteErrorReport;

/**
 * Set the delegate and selector to call when a crash occurs.
 * The selector must take an NSException* and NSArray* parameter like so: <br>
 * - (void) notifyException:(NSException*) exception stackTrace:(NSArray*) stackTrace <br>
 * stackTrace will be an array of StackTraceEntry.
 *
 * @param delegate The delegate to call.
 * @param selector The selector to invoke.
 */
- (void) setCrashDelegate:(id) delegate selector:(SEL) selector;
@end
