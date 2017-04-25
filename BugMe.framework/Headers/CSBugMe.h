//
//  CSBugMe.h
//  BugMe
//
//  Created by Charanjit Singh on 17/10/16.
//  Copyright © 2016 Charanjit Singh. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CSReachability.h"

@interface CSBugMe : NSObject
@property(nonatomic,retain)NSString* appKey;
@property (nonatomic) CSReachability *internetReachability;
/*!
 Set this Bool value to check application version and OS Version.
*/

@property (nonatomic) BOOL wantToCheckVersion;


-(void)crashReportForSecretKey:(NSString*)key;

/*!
 Check Application version and OS version of the application
 */
-(void)checkApplicationVersion:(NSString*)key;

- (void) notifyException:(NSException*) exception stackTrace:(NSArray*) stackTrace;
-(void)apiToSendCrashReportToServer:(NSDictionary*)dict;
-(void)getLogs:(id)sender;
-(void)uploadLog:(id)Value forKey:(NSString*)key;
/*!
 CSBUGMe provides the methods to send controllers and events name to the
server.
 Set ViewController and Action Name 
 
 @param viewController contain the controller in which currently user present and eventName contain the action performed by user.
 
 */
-(void)setController:(id)viewController MeasureAction:(NSString *)eventName;
+ (instancetype)sharedInstance;
//SYNTHESIZE_SINGLETON_FOR_CLASS_HEADER(CSBugMe);

@end
