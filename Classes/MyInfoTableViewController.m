//
//  MyInfoTableViewController.m
//  FamilyTree
//
//  Created by Kyungil Kim on 1/4/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "MyInfoTableViewController.h"
#import "Constants.h"


@implementation MyInfoTableViewController

@synthesize delegate;
@synthesize imageView;
@synthesize nameTableView;
@synthesize nameLabel;
@synthesize person;

/*
- (id)initWithStyle:(UITableViewStyle)style {
    // Override initWithStyle: if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
    if (self = [super initWithStyle:style]) {
    }
    return self;
}
*/


- (void)returnToTree {
	[self.delegate tableViewController:self reloadNames:NO reloadTree:NO];
}

- (void)setEditing:(BOOL)editing animated:(BOOL)animated {
	[super setEditing:editing animated:animated];
	
	[nameTableView setEditing:editing animated:animated];
	
	[nameTableView reloadRowsAtIndexPaths:[NSArray arrayWithObject:[NSIndexPath indexPathForRow:0 inSection:0]] withRowAnimation:UITableViewRowAnimationNone];
	
}

- (void)viewDidLoad {
    [super viewDidLoad];

    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
	nameTableView.allowsSelection = NO;
	
    self.navigationItem.rightBarButtonItem = self.editButtonItem;
	
	UIButton *treeButton = [[UIButton alloc] initWithFrame:CGRectMake(0, 0, BUTTON_SIZE, BUTTON_SIZE)];
	[treeButton addTarget:self action:@selector(returnToTree) forControlEvents:UIControlEventTouchUpInside];
	NSString *imagePath = [[NSBundle mainBundle] pathForResource:@"TreeButton" ofType:@"png"];
	UIImage *image = [[UIImage alloc] initWithContentsOfFile:imagePath];
	[treeButton setBackgroundImage:image forState:UIControlStateNormal];
	[image release];
	
	UIBarButtonItem *buttonItem = [[UIBarButtonItem alloc] initWithCustomView:treeButton];
	[treeButton release];
	self.navigationItem.leftBarButtonItem = buttonItem;
	[buttonItem release];
	
	if (person.thumbnailImage == nil) {
		imagePath = [[NSBundle mainBundle] pathForResource:@"NoPicture_White" ofType:@"png"];
		image = [[UIImage alloc] initWithContentsOfFile:imagePath];
		imageView.image = image;
		[image release];
	}
	
	nameLabel = [[UILabel alloc] initWithFrame:CGRectMake(6, 9, 198, 43)];
	nameLabel.font = [UIFont boldSystemFontOfSize:18];
	nameLabel.adjustsFontSizeToFitWidth = YES;
	nameLabel.backgroundColor = [UIColor clearColor];
	nameLabel.text = [person compositeName];
}


/*
- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
}
*/
/*
- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
}
*/
/*
- (void)viewWillDisappear:(BOOL)animated {
	[super viewWillDisappear:animated];
}
*/
/*
- (void)viewDidDisappear:(BOOL)animated {
	[super viewDidDisappear:animated];
}
*/

/*
// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
*/

- (void)didReceiveMemoryWarning {
	// Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
	
	// Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
	// Release any retained subviews of the main view.
	// e.g. self.myOutlet = nil;
	self.navigationItem.rightBarButtonItem = nil;
	self.navigationItem.leftBarButtonItem = nil;
	self.imageView = nil;
	self.nameTableView = nil;
	self.nameLabel = nil;
}


#pragma mark Table view methods

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    if (tableView == self.tableView) {
		return 1;
	} else {
		return 1;
	}
}


// Customize the number of rows in the table view.
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	if (tableView == self.tableView) {
		return 2;
	} else {
		return 1;
	}
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
	if (tableView == self.tableView) {
		return 44.0;
	} else {
		return 63.0;
	}
}


// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
	
	UITableViewCell *cell = nil;
	static NSString *CellIdentifier = nil;
	
	if (tableView == self.tableView) {
		CellIdentifier = @"Cell";
		
		cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
		if (cell == nil) {
			cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
		}
	} else {
		if (tableView.editing) {
			CellIdentifier = @"NameCellEditing";
		} else {
			CellIdentifier = @"NameCell";
		}
		
		cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
		if (cell == nil) {
			cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
			if (!tableView.editing) {
				UIView *transparentBackground = [[UIView alloc] initWithFrame:CGRectZero];
				transparentBackground.backgroundColor = [UIColor clearColor];
				cell.backgroundView = transparentBackground;
				[transparentBackground release];
			}
		}
		[cell.contentView addSubview:nameLabel];
	}
    
    // Set up the cell...
	cell.editingAccessoryType = UITableViewCellAccessoryDisclosureIndicator;
    return cell;
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	[tableView deselectRowAtIndexPath:indexPath animated:YES];
    // Navigation logic may go here. Create and push another view controller.
	// AnotherViewController *anotherViewController = [[AnotherViewController alloc] initWithNibName:@"AnotherView" bundle:nil];
	// [self.navigationController pushViewController:anotherViewController];
	// [anotherViewController release];
}


/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/

- (UITableViewCellEditingStyle)tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath {
	if (tableView == self.tableView) {
		return UITableViewCellEditingStyleDelete;
	} else {
		return UITableViewCellEditingStyleNone;
	}
}


/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:YES];
    }   
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/

- (BOOL)tableView:(UITableView *)tableView shouldIndentWhileEditingRowAtIndexPath:(NSIndexPath *)indexPath {
	if (tableView == self.tableView) {
		return YES;
	} else {
		return NO;
	}
}


/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath {
}
*/


/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/


- (void)dealloc {
	[imageView release];
	[nameTableView release];
	[nameLabel release];
	[person release];
    [super dealloc];
}


@end

