#include<iostream>
#include<string>
using namespace std;
struct User
{
	int userId;
	char userName[50];
	char password[50];
};
struct Tweet
{
	char tweet[180];
	char userName[50];
	int userId;

};
struct Follow
{
	int userId;
	int followedUserId;
};
User* users = NULL;
int globalSize = 100;

//this global object is to used to set all the indeces of the user array to the values 
//stored in it for each member.

User defaultUser{ -1,'\0','\0' };
User currentUser = { -1,'\0','\0' };

void signUp();
void readUsersFromFile(User usersArray[]);
void writeUsersToFile(User newUser);
void login();
void addTweet();
void viewTweet();
void followUser();
bool isEqual(char arr1[], char arr2[]);
void writeTweetToFile(Tweet t);
void writeFollowerToFile(Follow f);

int main()
{
	int size = 100;
	globalSize = size;
	cout << "Initializing the system....\n";
	users = new User[size];


	for (int i = 0; i < size; i++)
	{
		users[i] = defaultUser;
	}
	readUsersFromFile(users);

	cout << "\t\t\t\t\t\t******Welcome to Eagle ******\n\t\t\t\t\t\t| " << __TIMESTAMP__ << " |\n";
	char ask;

	do
	{

		cout<< "Press L to Login\n"
			<< "Press S to Signup\n"
			<< "Press X to exit\n";
		cin >> ask;
		cin.ignore();
		system("CLS");
		if (ask == 'l' || ask == 'L')
		{
			login();
		}
		else if (ask == 's' || ask == 'S')
		{
			signUp();
		}

	} while (ask != 'x' && ask != 'X');
	return 0;

}


void signUp()
{
		User u;
		cout << "Enter User Name: ";
		cin.getline(u.userName, 50);
		cout << "\nEnter password: ";
		cin.getline(u.password, 50);

		bool checkEmpty = 0;
		bool alreadyExist = 0;

		do
		{
			alreadyExist = 0;
			for (int i = 0; i < globalSize; i++)
			{
				if (isEqual(u.userName, users[i].userName) == 1)
				{
					alreadyExist = 1;
					cout << "Entered user name already exist\nRe-enter user name: ";
					cin.getline(u.userName, 50);
					break;
				}
			}
		} while (alreadyExist == 1);


			for (int i = 0; i < globalSize; i++)
			{
				if (users[i].userId == -1)
				{
					checkEmpty = 1;
					u.userId = i;
					users[i] = u;
					cout << "\t\t\t\t\tAccount created\n\n";
					writeUsersToFile(users[i]);
					break;
				}
			}
		if (checkEmpty != 1)
		{
			cout << "\nAccount can't be created\n";
		}
}
void readUsersFromFile(User usersArray[])
{
	FILE* infile;
	User u;
	int i = 0;
	// Open Users.dat for reading 
	fopen_s(&infile, "Users.dat", "r");
	if (infile == NULL) {
		cout << "\nUsers file is empty\n";
		return;
	}
	// read file contents till end of file 
	while (fread(&u, sizeof(User), 1, infile))
	{
		usersArray[i] = u;
		i++;
	}
	fclose(infile);
}
void writeUsersToFile(User newUser)
{
	FILE* outfile;
	// open file for writing 
	fopen_s(&outfile, "Users.dat", "a+");
	if (outfile == NULL)
	{
		cout << "\nError in creating/opening file\n";
		return;
	}
	// write struct to file 
	fwrite(&newUser, sizeof(User), 1, outfile);

	if (fwrite != 0)
		cout << "contents to file written successfully !\n";
	else
		cout << "error writing file !\n";

	// close file 
	fclose(outfile);
}
void login()
{
	char uN[50]; //un is used to take userName as input.
	char pass[50]; //pass is used to take password as input.
	bool uNMatched = 0, passMatched = 0;
	//cin.ignore();
	cout << "Enter your UserName: ";
	cin.getline(uN, 50);
	cout << "\nEnter your Password: ";
	cin.getline(pass, 50);

	//The loop for searching and authenticating the user
	for (int i = 0; i < globalSize; i++)
	{
		if (isEqual(uN, users[i].userName) == 1)
		{
			uNMatched = 1;
			do
			{
				if (isEqual(pass, users[i].password) == 1)
				{
					passMatched = 1;
					currentUser = users[i];
					break;//This break will terminate the do while loop
				}
				else
				{
					cout << "Invalid Password entered\n" << "Re-enter Password: ";
					cin.getline(pass, 50);
				}
			} while (passMatched != 1);
			break; //This break will terminate the for loop


		}
	}

	//If found and authenticated then the following code will execute
	if (uNMatched == 1 && passMatched == 1)
	{
		char ask;
		do
		{

			cout<< "Press T to add a tweet\n"
				<< "Press V to view a tweet\n"
				<< "Press F to follow a user\n"
				<< "Press X to logout\n";
			cin >> ask;
			cin.ignore();
			system("CLS");
			if (ask == 't' || ask == 'T')
			{
				addTweet();
			}
			else if (ask == 'v' || ask == 'V')
			{
				viewTweet();
			}
			else if (ask == 'f' || ask == 'F')
			{
				followUser();
			}

		} while (ask != 'x' && ask != 'X');
	}
	//If not found then the following lines will be executed
	else
	{
		cout << "The userName you entered does'nt exist\n";
	}


}
void addTweet()
{
	string t;
	Tweet tweet;
	int endOfTweet = 0;
	cout << "\nYour tweet should be of 180 characters else the system will trim it\n";
	cout << "Type your tweet: ";
	getline(cin, t);
	do
	{
		if (t.length() > 180)
		{
			cout << "\n\nYour tweet contains " << t.length() << " characters. \n\nReduce it to 180!\nRe-enter tweet: ";
			getline(cin, t);
		}
	} while (t.length() > 180);

	for (int i = 0; i < t.length(); i++)
	{
		tweet.tweet[i] = t[i];
		endOfTweet = i;
	}
	tweet.tweet[endOfTweet + 1] = '\0';
	tweet.userId = currentUser.userId;
	for (int i = 0; i < 50; i++)
	{
		tweet.userName[i] = currentUser.userName[i];

	}

	writeTweetToFile(tweet);
	system("CLS");
}
void viewTweet()
{
		Tweet tweet;
		Follow follow;
		int displayedTweets = 0;

		FILE* infileTweet;
		Tweet t;
		// Open Followers.dat for reading 
		fopen_s(&infileTweet, "Tweet.dat", "r");
		if (infileTweet == NULL)
		{
			cout << "\nNo tweets to show\n";

			fclose(infileTweet);
			return;
		}
		
		else
		{
			FILE* infileFollowers;
			Follow f;
			// Open Followers.dat for reading 
			fopen_s(&infileFollowers, "Followers.dat", "r");
			//If we have tweets and NOT the followers then the code in following IF statement will be executed
			if (infileFollowers == NULL)
			{
				cout << "\nShowing random tweets\n";
				while (fread(&t, sizeof(Tweet), 1, infileTweet))
				{
					cout << t.tweet << endl << "UserName: " << t.userName << " Not Following" << endl;
					displayedTweets++;
					if (displayedTweets == 10)
					{
						break;
					}
				}
				fclose(infileTweet);
				return;
			}

			//If we have tweets and the followers then the code in following else will be executed
			else
			{
				displayedTweets = 0;
				// read Followers file contents till end of file
				while (fread(&f, sizeof(Follow), 1, infileFollowers))
				{
					
					if (currentUser.userId == f.userId)
					{
						// read Tweet file contents till end of file
						fopen_s(&infileTweet, "Tweet.dat", "r");
						while (fread(&t, sizeof(Tweet), 1, infileTweet))
						{
							
							if (f.followedUserId == t.userId)
							{
								displayedTweets++;
								if (displayedTweets == 10)
								{
									break;
								}
								cout << t.tweet << endl << "UserName: " << t.userName << " Following" << endl;
							}
						}
						fclose(infileTweet);
						
					}

					if (displayedTweets == 10)
					{
						break;
					}
				}

				if (displayedTweets == 0)
				{
					while (fread(&t, sizeof(Tweet), 1, infileTweet))
					{

						if (displayedTweets == 10)
						{
							break;
						}
						cout << t.tweet << endl << "UserName: " << t.userName << endl;
						displayedTweets++;
					}
				}
			}
			fclose(infileFollowers);
		}
		/*fclose(infileTweet);*/
	}
void followUser()
{
	char uN[50];
	bool uNMatched = 0;
	Follow follow;
	cout << "Enter a userName\n";
	cin.getline(uN, 50);

	for (int i = 0; i < globalSize; i++)
	{
		if (isEqual(uN, users[i].userName) == 1)
		{
			uNMatched = 1;
			cout << "\nSearched user found\n";
			follow.userId = currentUser.userId;
			follow.followedUserId = users[i].userId;
			cout << "You are now following: " << users[i].userName << endl;
			writeFollowerToFile(follow);
			break; //This break will terminate the for loop
		}
	}
}
bool isEqual(char arr1[], char arr2[]) {
	int sizeOfArr1 = 0;
	int sizeOfArr2 = 0;
	int index = 0;
	while (arr1[index] != '\0') {
		sizeOfArr1++;
		index++;
	}
	index = 0;
	while (arr2[index] != '\0') {
		sizeOfArr2++;
		index++;
	}
	if (sizeOfArr1 != sizeOfArr2)
		return false;
	else {
		for (int i = 0; i < sizeOfArr1; i++) {
			if (arr1[i] != arr2[i]) {
				return false;
			}
		}
		return true;
	}
}
void writeTweetToFile(Tweet t)
{
	FILE* outfile;
	// open file for writing 
	fopen_s(&outfile, "Tweet.dat", "a+");
	if (outfile == NULL)
	{
		cout << "\nError in creating/opening file\n";
		return;
	}
	// write struct (Tweet) to file 
	fwrite(&t, sizeof(Tweet), 1, outfile);

	if (fwrite != 0)
		cout << "contents to file written successfully !\n";
	else
		cout << "error writing file !\n";

	// close file 
	fclose(outfile);
}
void writeFollowerToFile(Follow f)
{
	FILE* outfile;
	// open file for writing 
	fopen_s(&outfile, "Followers.dat", "a+");
	if (outfile == NULL)
	{
		cout << "\nError in creating/opening file\n";
		return;
	}
	// write struct (Follow) to file 
	fwrite(&f, sizeof(Follow), 1, outfile);

	if (fwrite != 0)
		cout << "contents to file written successfully !\n";
	else
		cout << "error writing file !\n";

	// close file 
	fclose(outfile);
}
