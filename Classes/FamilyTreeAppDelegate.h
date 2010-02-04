//
//  FamilyTreeAppDelegate.h
//  FamilyTree
//
//  Created by Kyungil Kim on 1/2/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

@interface FamilyTreeAppDelegate : NSObject <UIApplicationDelegate> {
    
    UIWindow *window;
    UINavigationController *navigationController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet UINavigationController *navigationController;

@end

