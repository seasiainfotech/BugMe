//
//  NSString+SHA.h
//  CrashManager
//
//  Created by Charanjit Singh on 17/10/16.
//  Copyright © 2016 Charanjit Singh. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (SHA)

- (NSString *)sha1;
- (NSString *)sha224;
- (NSString *)sha256;
- (NSString *)sha384;
- (NSString *)sha512;


@end
