//
//  SettingsTableViewController.h
//  FamilyTree
//
//  Created by Kyungil Kim on 1/3/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol SettingsTableViewControllerDelegate;

@interface SettingsTableViewController : UITableViewController {
	id<SettingsTableViewControllerDelegate> delegate;
	
	UISwitch *treeModeSwitch;
	UISwitch *hebrewCalendarSwitch;
	UISwitch *lunarCalendarSwitch;
	UISwitch *lastNameOnTheTreeSwitch;
	char nameOrderSelectedRow;
	
	BOOL previousValueOfTreeModeSwitch;
	BOOL previousValueOfHebrewCalenderSwitch;
	BOOL previousValueOfLunarCalenderSwitch;
	BOOL previousValueOfLastNameOnTheTreeSwitch;
	char previousValueOfNameOrderSelectedRow;
}

@property (nonatomic, assign) id<SettingsTableViewControllerDelegate> delegate;
@property (nonatomic, retain) UISwitch *treeModeSwitch;
@property (nonatomic, retain) UISwitch *hebrewCalendarSwitch;
@property (nonatomic, retain) UISwitch *lunarCalendarSwitch;
@property (nonatomic, retain) UISwitch *lastNameOnTheTreeSwitch;

@end

@protocol SettingsTableViewControllerDelegate <NSObject>

- (void)tableViewController:(UITableViewController *)tableViewController reloadNames:(BOOL)reloadNames reloadTree:(BOOL)reloadTree;

@end
