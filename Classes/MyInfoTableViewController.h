//
//  MyInfoTableViewController.h
//  FamilyTree
//
//  Created by Kyungil Kim on 1/4/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Person.h"

@protocol MyInfoTableViewControllerDelegate;

@interface MyInfoTableViewController : UITableViewController {
	id<MyInfoTableViewControllerDelegate> delegate;
	
	IBOutlet UIImageView *imageView;
	IBOutlet UITableView *nameTableView;
	UILabel *nameLabel;
	
	Person *person;
}

@property (nonatomic, assign) id<MyInfoTableViewControllerDelegate> delegate;
@property (nonatomic, retain) UIImageView *imageView;
@property (nonatomic, retain) UITableView *nameTableView;
@property (nonatomic, retain) UILabel *nameLabel;
@property (nonatomic, retain) Person *person;

@end

@protocol MyInfoTableViewControllerDelegate <NSObject>

- (void)tableViewController:(UITableViewController *)tableViewController reloadNames:(BOOL)reloadNames reloadTree:(BOOL)reloadTree;

@end