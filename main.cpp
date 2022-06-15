
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>

using namespace std;

//globale variables:
int costmrID =0;
int employID =0;

//structuer:
struct Record{
    string Name;
    string Email;
    string Phone;
    string Region;
    char Password[9];
    int ID;
};
struct service{
	string carType;
	string package;
	string packPrice;
	string contact;
	string time;
	string payment;
};

//functions decleration for the first part of the program: [4 FUNCTIONS]
void getData (Record record[], int personID);
void getORgenrtPass (string Name, string Email, string Phon, string Regon, char pass[], int ID);
char * rotatedARR (string Name, string Email, string Phon, string Regon); //not important
void SignIn (string Name, char pass[], int & ErrorPass);

//functions decleration for the second part of the program: [2 FUNCTIONS]
void SERVICE (service serviceDATA[], int personID);
void SERVICE_2 (service serviceDATA[], int personID);

//functions decleration for the third part of the program: [6 FUNCTIONS]
void update (Record recordCOSTMR[], Record recordEMPLOY[], service serviceDATA[], int CostmrID, int EmployID);
int BinarySearch (Record record[], int first, int last, string search_name);
void Delete (Record record[], int Index, int numberOFrecords);
void Delete (service serviceDATA[], int Index, int numberOFrecords);
void print (Record record[], int personID);
void print (service serviceDATA[], int personID);

int main(){
    Record recordCostmr[100];
    service serviceDATA[100];
    Record recordEmploy[50];
	
	int IDchk;
	
	//creating input file object
	ifstream inFile;
	
	//start of the program
	bool MainMenu = true;
	while(MainMenu){
		char CorE; //Costumer OR Employee?
		
		//displaying main menu
	    inFile.open("mainMENU.txt");
		if(inFile.is_open()==true){
			string menu;
			while(!inFile.eof()){
				getline(inFile, menu);
				cout<<menu<<endl;
			}
			inFile.close();
		}
		else
			cout<<"\nopen mainMENU.txt faild\n";
		cin>>CorE;
	    
	    if (CorE == 'a'){ //dealing with costumer data base
	    	bool con = true;
			while (con){
				//dispalying menu for costumer
				inFile.open("CostmrMENU.txt");
				if(inFile.is_open()==true){
					string menu;
					while(!inFile.eof()){
						getline(inFile, menu);
						cout<<menu<<endl;
					}
					inFile.close();
				}
				else
					cout<<"\nopen CostmrMENU.txt faild\n";
				char chos;
				cin>>chos;
				if (chos >= 0 && chos <=96 || chos >= 100){
					cout<<"ERROR invalid entery!"<<endl;
				}
				switch (chos){
				    case 'a': //create a new account (sign up)
				    	cout<<"---------------------------------------------------------\n";
				    	cin.ignore();
				    	getData(recordCostmr, costmrID);
				    	getORgenrtPass(recordCostmr[costmrID].Name, recordCostmr[costmrID].Email, recordCostmr[costmrID].Phone, recordCostmr[costmrID].Region, recordCostmr[costmrID].Password, recordCostmr[costmrID].ID);
				    	costmrID ++;
						break;
				    case 'c': //wnat to get back to main menu (costumer interface OR employee interface)
				    	con = false;
				    	break;
					case 'b': //already have an account (sign in)
						cout<<"---------------------------------------------------------\n";
						int ErrorPass = 0;
						while(ErrorPass == 0){
							//when fatimah entered 'a', she got an error! any way idk how to fix it :)
							cout<<"Enter ID: ";
							cin>>IDchk;
							SignIn(recordCostmr[IDchk].Name, recordCostmr[IDchk].Password, ErrorPass);
						}
						//starting the second part of the program
						cout<<"\n---------------------------------------------------------\n";
						cout<<"                  [ BOOKING A SERVICE ]";
						cout<<"\n---------------------------------------------------------\n";
						SERVICE (serviceDATA, IDchk);
						SERVICE_2 (serviceDATA, IDchk);
						cout<<"\nTHANK YOU FOR CHOOSING OUR SERVICES\n";
						con = false;
				    	break;
				}	
			}
		}
		else if (CorE == 'b'){ //dealing with employee interface
			bool con = true;
			while (con){
				//dispalying menu for Employee
				inFile.open("EmployMENU.txt");
				if(inFile.is_open()==true){
					string menu;
					while(!inFile.eof()){
						getline(inFile, menu);
						cout<<menu<<endl;
					}
					inFile.close();
				}
				else
					cout<<"\nopen EmployMENU.txt faild\n";
				char chos;
				cin>>chos;
				if (chos >= 0 && chos <=96 || chos >= 99){
					cout<<"ERROR invalid entery!"<<endl;
				}
				switch (chos){
				    case 'b': //wnat to get back to main menu (costumer interface OR employee interface)
				    	con = false;
				    	break;
					case 'a': //sign in to an employee account
				    	cout<<"\n---------------------------------------------------------\n";
						int ErrorPass = 0;
						while(ErrorPass == 0){
							cout<<"Enter ID: ";
							cin>>IDchk;
							SignIn(recordEmploy[IDchk].Name, recordEmploy[IDchk].Password, ErrorPass);
						}
						//starting the third part of the program
						while(true){
							cout<<"\n---------------------------------------------------------\n";
							cout<<"                   [ EMPLOYEE MENU ]";
							cout<<"\n---------------------------------------------------------\n";
							cout<<"a- UPDATE record\nb- DELETE record\nc- ADD new record\nd- DISPLAY record\ne- EXIT to main menu\n";
							char Chos;
							cin>>Chos;
							if (Chos == 'a'){ //for updating a record
								update ( recordCostmr, recordEmploy, serviceDATA, costmrID, employID);
							}
							else if (Chos == 'b'){ //for deleting a record
								while (true){
									cout<<"\n---------------------------------------------------------\n";
									cout<<"DELETE MENU:\na- Costumer Record\nb- Employee Record\nc- Exit to Employee Menu\n";
									char chos;
									cin>>chos;
									if(chos == 'a'){ //for deleting a costumer record
										while(true){
											string toBeDeleted;
											int index = -1;
											cout<<"---------------------------------------------------------\n";
											cin.ignore();
											cout<<"Enter costumer name to delete their record: ";
											getline(cin,toBeDeleted);
											index = BinarySearch (recordCostmr, 0, costmrID-1, toBeDeleted);
											if(index != -1){
												Delete (recordCostmr, index, costmrID-1);
												Delete (serviceDATA, index, employID-1);
												costmrID --;
												cout<<"the record has been deleted successfully";
												break;
											}
											else{
												cout<<"\nThe entered name dose not exist\n";
											}
										}
									}
									else if(chos == 'b'){ //for deleting an employee record
										while(true){
											string toBeDeleted;
											int index = -1;
											cout<<"---------------------------------------------------------\n";
											cin.ignore();
											cout<<"Enter employee name to delete their record: ";
											getline(cin,toBeDeleted);
											index = BinarySearch (recordEmploy, 0, employID-1, toBeDeleted);
											if(index != -1){
												Delete (recordEmploy, index, employID-1);
												employID --;
												cout<<"the record has been deleted successfully";
												break;
											}
											else{
												cout<<"\nThe entered name dose not exist\n";
											}
										}
									}
									else if(chos == 'c'){ //for exiting to employee menu
										break;
									}
									else{
										cout<<"ERROR invalid entery!";
									}
								}
							}
							else if (Chos == 'c'){ //for adding a new record
								while(true){
									cout<<"\n---------------------------------------------------------\n";
									cout<<"ADD MENU:\na- Costumer Record\nb- Employee Record\nc- Exit to Employee Menu\n";
									char chos;
									cin>>chos;
									if (chos == 'a'){ //for adding new costumer record
										cout<<"---------------------------------------------------------\n";
										cin.ignore();
										getData (recordCostmr, costmrID);
										getORgenrtPass(recordCostmr[costmrID].Name, recordCostmr[costmrID].Email, recordCostmr[costmrID].Phone, recordCostmr[costmrID].Region, recordCostmr[costmrID].Password, recordCostmr[costmrID].ID);
										costmrID++;
									}
									else if (chos == 'b'){ //for adding new employee record
										cout<<"---------------------------------------------------------\n";
										cin.ignore();
										getData (recordEmploy, employID);
										getORgenrtPass(recordEmploy[employID].Name, recordEmploy[employID].Email, recordEmploy[employID].Phone, recordEmploy[employID].Region, recordEmploy[employID].Password, recordEmploy[employID].ID);
										employID++;
									}
									else if (chos == 'c'){ //for exiting to employee menu
										break;
									}
									else{
										cout<<"ERROR invalid entery!";
									}	
								}
							}
							else if (Chos == 'd'){ //for dispalying a record
								while(true){
									cout<<"\n---------------------------------------------------------\n";
									cout<<"PRINT MENU:\na- Costumer Record\nb- Employee Record\nc- Exit to Employee Menu\n";
									char chos;
									cin>>chos;
									if (chos == 'a'){ //for printing costumer record
										cout<<"---------------------------------------------------------\n";
										cout<<"Enter Costumer ID to print their record: ";
										cin>>IDchk;
										cout<<"---------------------------------------------------------\n";
										print (recordCostmr, IDchk);
										print (serviceDATA, IDchk);
									}
									else if (chos == 'b'){ //for printing employee record
										cout<<"---------------------------------------------------------\n";
										cout<<"Enter Employee ID to print their record: ";
										cin>>IDchk;
										cout<<"---------------------------------------------------------\n";
										print (recordEmploy, IDchk);
									}
									else if (chos == 'c'){ //for exiting to employee menu
										break;
									}
									else{
										cout<<"ERROR invalid entery!";
									}	
								}
							}
							else if (Chos == 'e'){ //for exiting to the main menu
								break;
							}
							else{
								cout<<"ERROR invalid entry!";
							}
						}
						
						con = false;
				    	break;	
				}
			}
		}
		else if(CorE == 'c'){
			MainMenu = false; //end of the entire program
		}
		else
			cout<<"ERROR invalid entry!"<<endl;	
	}
	
    return 0;
}

//functions definition for the first part of the program:
void getData (Record record[], int personID){
	cout<<"Enter Name: ";
    getline(cin,record[personID].Name);
    cout<<"Enter Email: ";
    getline(cin,record[personID].Email);
    cout<<"Enter Phone Number: ";
    getline(cin,record[personID].Phone);
    cout<<"Enter Region: ";
    getline(cin,record[personID].Region);
    record[personID].ID = personID;
}
void getORgenrtPass (string Name, string Email, string Phon, string Regon, char pass[], int ID){
    
    while(true){
    	cout<<"\nchoose:\na-create your own password\nb-program to generate a suggested password\n";
	    char chose;
	    cin>>chose;
    	
	    if (chose == 'a'){ //create your own password 
	    	cout<<"---------------------------------------------------------\n";
	        cout<<"enter your password it must be a password of 8 charecters:\n>> ";
	        for(int i=0; i<8; i++)
	        	cin>>pass[i];
	        cout<<"---------------------------------------------------------\n";
	        cout<<"your password is: ";
	        cout<<pass;
	        cout<<"\nyour ID is: "<<ID<<endl;
	        break;
	    }
	    else if (chose == 'b'){ //program to generate a suggested password
	    	cout<<"---------------------------------------------------------\n";
			char * x = rotatedARR(Name, Email,  Phon, Regon);
	        int len = strlen(x);
		    srand(time(0));
		    char chr;
			cout<<"your password is: ";
		    for(int i=0; i<8; i++){
				chr = x[rand()%len];
	        	if ((chr >= 48 && chr <= 57) || (chr >= 65 && chr <= 90) || (chr >= 97 && chr <=122)){
	        		pass[i]=chr;
	        		cout<<pass[i];
				}
				else{
					pass[i]='0';
	        		cout<<pass[i];
				}
	    	}
			cout<<"\nyour ID is: "<<ID<<endl;
			break;	
		}
		else{
			cout<<"ERROR invalid entery!";
			cout<<"\n---------------------------------------------------------\n";
		}	
	}
	
}
char * rotatedARR (string Name, string Email, string Phon, string Regon){
	//converting strings variables into charachter arrays
	int nameSize = Name.length();
	char arrName[nameSize+1];
	for (int i = 0; i<nameSize; i++){
		arrName[i] = Name[i];
	}
	int emailSize = Email.length();
	char arrEmail[emailSize+1];
	for (int i = 0; i<emailSize; i++){
		arrEmail[i] = Email[i];
	}
	int phonSize = Phon.length();
	char arrPhon[phonSize+1];
	for (int i = 0; i<phonSize; i++){
		arrPhon[i] = Phon[i];
	}
	int regonSize = Regon.length();
	char arrRegon[regonSize+1];
	for (int i = 0; i<regonSize; i++){
		arrRegon[i] = Regon[i];
	}
	
	//concatenating previous character arrays into one character array
	int sizeY = nameSize + emailSize + phonSize + regonSize;
	char Y[sizeY+1];
	strcpy(Y, arrName);
	strcat(Y, arrEmail);
	strcat(Y, arrPhon);
	strcat(Y, arrRegon);
	int lenY = strlen(Y); //i think this line is th problem
	
	//rotating array Y:
	int repose;
	srand(time(0));
	repose = 6+rand()%(15 -6 +1);
	int newIndex;
	char * rotateY = new char [sizeY+1]; //daynamic array
	for (int i=0; i < sizeY; i++){
		newIndex = i + repose;
		if (newIndex > sizeY)
			newIndex = newIndex % sizeY;
		rotateY[newIndex] = Y[i];
	}
	
	return rotateY;
}
void SignIn (string Name, char pass[], int & ErrorPass){
    char passChk[9];
	bool valid = true;
	cout<<"Enter password: ";
	for(int i = 0; i<8; i++){
	    cin>>passChk[i];
	}
	for(int i=0; i<8; i++){
	    if(pass[i] != passChk[i]){
	    	valid = false;
	    	//ErrorPass = 0;
			cout<<"ERROR incorrect ID or password!"<<endl;
	    	cout<<"---------------------------------------------------------\n";
	    	break;
	    }
	}
	if (valid){
		cout<<"\t{ "<<Name<<", welcome to your account }"<<endl;
		ErrorPass = 1;
	}
}

//functions definition for the second part of the program:
void SERVICE (service serviceDATA[], int personID){
	cout<<"Type Of Car:\na- Large Car [7 Occupant]\nb- Medium Car [5 Occupant]\nc- Small Car [sedan]\n";
	char chos;
	cin >> chos;
	
	if (chos == 'a'){ //large car
	    serviceDATA[personID].carType = "Large Car";
	    cout<<"---------------------------------------------------------\n";
	    while(true){
	    	cout<<"Packages For Large Car:\na- Wax Polishing\nb- Agency Polishing\nc- Nano Washing\nd- For more information about packages\n";
		    char pack;
		    cin>>pack;
		    if (pack == 'a'){
		    	serviceDATA[personID].package = "Wax Polishing";
		    	serviceDATA[personID].packPrice = "395 SR";
		    	break;
			}
			else if(pack == 'b'){
				serviceDATA[personID].package = "Agency Polishing";
		    	serviceDATA[personID].packPrice = "935 SR";
		    	break;
			}
			else if (pack == 'c'){
				serviceDATA[personID].package = "Nano Washing";
		    	serviceDATA[personID].packPrice = "85 SR";
		    	break;
			}
			else if (pack == 'd'){
				//creating file object (lecture 11)
				ifstream inFile;
				//dispalying more information about packages
				inFile.open("packagesINFO.txt");
				if(inFile.is_open()==true){
					string menu;
					while(!inFile.eof()){
						getline(inFile, menu);
						cout<<menu<<endl;
					}
					inFile.close();
				}
				else
					cout<<"\nopen packagesINFO.txt faild\n";	
			}
			else{
				cout<<"ERROR Invalid entery!";
				cout<<"\n---------------------------------------------------------\n";
			}
		}
	}
	else if (chos == 'b'){ //medium car
		serviceDATA[personID].carType = "Medium Car";
		cout<<"---------------------------------------------------------\n";
		while(true){
	    	cout<<"Packages For Large Car:\na- Wax Polishing\nb- Agency Polishing\nc- Nano Washing\nd- For more information about packages\n";
		    char pack;
		    cin>>pack;
		    if (pack == 'a'){
		    	serviceDATA[personID].package = "Wax Polishing";
		    	serviceDATA[personID].packPrice = "365 SR";
		    	break;
			}
			else if(pack == 'b'){
				serviceDATA[personID].package = "Agency Polishing";
		    	serviceDATA[personID].packPrice = "810 SR";
		    	break;
			}
			else if (pack == 'c'){
				serviceDATA[personID].package = "Nano Washing";
		    	serviceDATA[personID].packPrice = "85 SR";
		    	break;
			}
			else if (pack == 'd'){
				//creating file object (lecture 11)
				ifstream inFile;
				//dispalying more information about packages
				inFile.open("packagesINFO.txt");
				if(inFile.is_open()==true){
					string menu;
					while(!inFile.eof()){
						getline(inFile, menu);
						cout<<menu<<endl;
					}
					inFile.close();
				}
				else
					cout<<"\nopen packagesINFO.txt faild\n";	
			}
			else{
				cout<<"ERROR Invalid entery!";
				cout<<"\n---------------------------------------------------------\n";
			}
		}
	}
	else if(chos == 'c'){ //small car
		serviceDATA[personID].carType = "Small Car";
		cout<<"---------------------------------------------------------\n";
		while(true){
	    	cout<<"Packages For Large Car:\na- Wax Polishing\nb- Agency Polishing\nc- Nano Washing\nd- For more information about packages\n";
		    char pack;
		    cin>>pack;
		    if (pack == 'a'){
		    	serviceDATA[personID].package = "Wax Polishing";
		    	serviceDATA[personID].packPrice = "315 SR";
		    	break;
			}
			else if(pack == 'b'){
				serviceDATA[personID].package = "Agency Polishing";
		    	serviceDATA[personID].packPrice = "745 SR";
		    	break;
			}
			else if (pack == 'c'){
				serviceDATA[personID].package = "Nano Washing";
		    	serviceDATA[personID].packPrice = "75 SR";
		    	break;
			}
			else if (pack == 'd'){
				//creating file object (lecture 11)
				ifstream inFile;
				//dispalying more information about packages
				inFile.open("packagesINFO.txt");
				if(inFile.is_open()==true){
					string menu;
					while(!inFile.eof()){
						getline(inFile, menu);
						cout<<menu<<endl;
					}
					inFile.close();
				}
				else
					cout<<"\nopen packagesINFO.txt faild\n";	
			}
			else{
				cout<<"ERROR Invalid entery!";
				cout<<"\n---------------------------------------------------------\n";
			}
		}
	}
	else{
		cout << "ERROR invalid entry!";
		cout<<"\n---------------------------------------------------------\n";
		SERVICE (serviceDATA, personID);
	}
}
void SERVICE_2 (service serviceDATA[], int personID){
	cout<<"---------------------------------------------------------\n";
	while(true){
		cout<<"Contact Method:\na- Whatsupp\nb- Email\n";
		char chos;
		cin>>chos;
		if(chos == 'a'){
			serviceDATA[personID].contact = "Whatsupp";
			break;
		}
		else if(chos == 'b'){
			serviceDATA[personID].contact = "Email";
			break;	
		}
		else{
			cout<<"ERROR invalid intery!";
			cout<<"\n---------------------------------------------------------\n";
		}
	}
	cout<<"---------------------------------------------------------\n";
	while(true){
		cout<<"Appointment Time:\na- 9:00 AM\nb- 12:00 PM\nc- 6:00 PM\n";
		char chos;
		cin>>chos;
		if(chos == 'a'){
			serviceDATA[personID].time = "9:00 AM";
			break;
		}
		else if(chos == 'b'){
			serviceDATA[personID].time = "12:00 PM";
			break;	
		}
		else if(chos == 'c'){
			serviceDATA[personID].time = "6:00 PM";
			break;	
		}
		else{
			cout<<"ERROR invalid intery!";
			cout<<"\n---------------------------------------------------------\n";
		}
	}
	cout<<"---------------------------------------------------------\n";
	while(true){
		cout<<"Payment Method:\na- Credit Card\nb- Cash\n";
		char chos;
		cin>>chos;
		if(chos == 'a'){
			serviceDATA[personID].payment = "Credit Card";
			break;
		}
		else if(chos == 'b'){
			serviceDATA[personID].payment = "Cash";
			break;	
		}
		else{
			cout<<"ERROR invalid intery!";
			cout<<"\n---------------------------------------------------------\n";
		}
	}
}

//functions definition for the third part of the program:
void update (Record recordCOSTMR[], Record recordEMPLOY[], service serviceDATA[], int CostmrID, int EmployID){
	
	while(true){
		cout<<"\n---------------------------------------------------------\n";
		cout<<"UPDATE MENU:\na- Costumer Record\nb- Employee Record\nc- Exit to Employee Menu\n";
		char chos;
		cin>>chos;
		if(chos == 'a'){ //for updating a costumer record
			while(true){
				cout<<"\n---------------------------------------------------------\n";
				cout<<"Update:\na- Costumer Data\nb- Costumer's Appointment\nc- Exit to UPDATE MENU\n";
				char chos;
				cin>>chos;
				if(chos == 'a'){ //updating costumer data
					string toBeUpdated;
					int index = -1;
					cout<<"---------------------------------------------------------\n";
					cin.ignore();
					cout<<"Enter name to be updated: ";
					getline(cin,toBeUpdated);
					index = BinarySearch (recordCOSTMR, 0, CostmrID, toBeUpdated);
		
					if(index != -1){
						cout<<"\n---------------------------------------------------------\n";
						getData(recordCOSTMR, index);
					}
					else{
						cout<<"\nThe entered name dose not existed\n";
					}
				}
				else if (chos == 'b'){ //updating costumer's appointment
					string name;
					int IDchk;
					cout<<"---------------------------------------------------------\n";
					cin.ignore();
					cout<<"Enter Costumer name: ";
					getline(cin, name);
					cout<<"Enter ID of costumer: ";
					cin>>IDchk;
					cout<<"---------------------------------------------------------\n";
					SERVICE (serviceDATA, IDchk);
					SERVICE_2(serviceDATA, IDchk);
				}
				else if (chos == 'c'){
					break;
				}
				else{
					cout<<"ERROR invalid entry!";
				}
			}
		}
		else if (chos == 'b'){ //for updating employee record
			
			string toBeUpdated;
			int index = -1;
			cout<<"---------------------------------------------------------\n";
			cin.ignore();
			cout<<"Enter name to be updated: ";
			getline(cin,toBeUpdated);
			index = BinarySearch (recordEMPLOY, 0, EmployID, toBeUpdated);
			
			if(index != -1){
				cout<<"\n---------------------------------------------------------\n";
				getData(recordEMPLOY, index);
				}
				else{
					cout<<"\nThe entered name dose not existed\n";
			}	
		}
		else if (chos == 'c'){
			break;
		}
		else{
			cout<<"ERROR invalid entry!";
		}
	}
}
int BinarySearch (Record record[], int first, int last, string search_name){
	int mid;
	if(last >= first){
		mid = (first + last)/2;
		if(record[mid].Name == search_name)
			return mid;
		else if (record[mid].Name < search_name)
			return BinarySearch( record, mid+1, last, search_name);
		else
			return BinarySearch( record, first, mid-1, search_name);
	}
	return -1;
}
void Delete (Record record[], int Index, int numberOFrecords){
	
	//code for deleting a record
	for (int i = Index; i < numberOFrecords ; i++){
		record[i].Name = record[i+1].Name;
		record[i].Email = record[i+1].Email;
		record[i].Phone = record[i+1].Phone;
		record[i].Region = record[i+1].Region;
		for(int j=0; j<8; j++){
			record[i].Password[j] = record[i+1].Password[j];
		}
	}
	
}
void Delete (service serviceDATA[], int Index, int numberOFrecords){
	
	//code for deleting a record
	for (int i = Index; i < numberOFrecords -1 ; i++){
		serviceDATA[i].package = serviceDATA[i+1].package;
		serviceDATA[i].packPrice = serviceDATA[i+1].packPrice;
		serviceDATA[i].contact = serviceDATA[i+1].contact;
		serviceDATA[i].time = serviceDATA[i+1].time;
		serviceDATA[i].payment = serviceDATA[i+1].payment;
	}
	
}
void print (Record record[], int personID){
	cout<<"Name: "<<record[personID].Name<<endl;
    cout<<"Email: "<<record[personID].Email<<endl;
    cout<<"Phone Number: "<<record[personID].Phone<<endl;
    cout<<"Region: "<<record[personID].Region<<endl;
    cout<<"Password: "<<record[personID].Password;
    cout<<"\nID: "<<personID<<endl;
}
void print (service serviceDATA[], int personID){
	cout<<"Type of car: "<<serviceDATA[personID].carType<<endl;
    cout<<"Package: "<<serviceDATA[personID].package<<endl;
    cout<<"Package's price: "<<serviceDATA[personID].packPrice<<endl;
    cout<<"Contact method: "<<serviceDATA[personID].contact<<endl;
    cout<<"Appointment time: "<<serviceDATA[personID].time<<endl;
    cout<<"Payment method: "<<serviceDATA[personID].payment<<endl;
}
