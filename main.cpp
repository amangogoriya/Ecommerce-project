#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

class User{
	private:
		int id;
		string username;
		string password;
		vector<pair<int,int> > wishlist;
		int ammount=0;
	public:
		User(){}
		User(int i,string usr,string pwd){
			id = i;
			username = usr;
			password = pwd;
		}
		int isAllowed(string pwd){
			return pwd==password;
		}
		void updateAmmount(int a){
			ammount+=a;
		}
		void addToWishlist(int pId,int q){
			wishlist.push_back({pId,q});
		}
		int totalAmmount(){
			int amt = ammount;
			ammount =0;
			return amt;
		}

		vector<pair<int,int> > getWishlist(){
			return wishlist;
		}
};


class Product{
	private :
		int id;
		int price;
		int quantity;
		string name;
		string description;
	public :
		Product(int i,int pr, int q,string n,string d){
			id = i;
			price = pr;
			quantity = q;
			name = n;
			description = d;
		}

		int buy(int q){
			if(q<=quantity){
				quantity -=q;
				return q*price;
			}	
			else {
				cout << "Product not available at the moment!"<<endl;
				return 0;
			}
		}
		
		int getId(){
			return id;
		}

		string getName(){
			return name;
		}

		string getDescription(){
			return description;
		}
		
		int getQuantity(){
			return quantity;
		}
		int getPrice(){
			return price;
		}
};

class Flipkart{
	private :
		vector<Product> p;
		vector<User> u;
		unordered_map<string,int> map;
		User currUser;
	public :
		void addProduct(){
			int id = p.size();
			int price,quantity;
			string name,description;
			int c=0;
			cout << "Name of the Product : "<<endl;
			getline(cin,name);
			cout << "Description of the Product : "<<endl;
			getline(cin,description);
			cout << "Price of the Product : "<<endl;
                        cin >> price;
			cout << "Quantity of the Product : "<<endl;
                        cin >> quantity;
			cin.ignore(1,'\n');
			Product pr(id,price,quantity,name,description);
			p.push_back(pr);
		}

		void checkOut(){
			cout << "\nProductName \t quantity \t price \t";
			for(auto x : currUser.getWishlist()){
				cout << p[x.first].getName() << " \t " << x.second << " \t " << x.second*p[x.first].getPrice()<<endl;
			}
			cout << "Total Ammount : " << currUser.totalAmmount()<<endl;
		}
		void printProducts(){
			cout << "Id \t Name \t Price \t Quantity"<<endl;
			for(int i=0;i<p.size();i++){
				cout << p[i].getId()+1 <<" \t "<< p[i].getName() << " \t " << p[i].getPrice()<<" \t " << p[i].getQuantity() <<endl;
			}
			cout << "\nEnter product id to buy it or Enter 0 for checkout or Enter -1 for Signout"<<endl;
			int t;
			cin >> t;
			if(t==0)checkOut();
			else if(t==-1){
				homePage();
			}
			else{
				t--;
				cout << "Enter the quantity of the product"<<endl;
				int q;
				cin >> q;
				int amt = p[t].buy(q);
				currUser.updateAmmount(amt);
				if(amt)currUser.addToWishlist(t,q);
				printProducts();
			}
		}
		void loginPage(){
			system("clear");
			string usr,pwd;
			cout << "Login" << endl;
			cout << "Username : ";
			cin >> usr;
			cout << "Password : ";
			cin >> pwd;
			if(map.find(usr)!=map.end()){
				User us = u[map[usr]];
				if(us.isAllowed(pwd)){
					currUser = us;
					cout << "You have been loggedin succesfully"<<endl;
					printProducts();
				}
				else{
					cout << "Wrong Password, press any key to try again;"<<endl;
					sleep(2);
					loginPage();
				}
			}
			else{
				cout << "Wrong Username, enter 1 to signup first or enter any other key to try again."<<endl;
				string st;
				cin >> st;
				if(st=="1"){
					signupPage();
				}
				else{
					sleep(2);
	                                loginPage();
				}
			}
		}
		void signupPage(){
			system("clear");
			cout << "Signup" << endl;
			int id = u.size();
                        string username;
                        string password;
                        cout << "Enter Username : "<<endl;
                        cin >> username;
                        cout << "Enter Password : "<<endl;
                        cin >> password;
			cout << "Your have signed up succesfully"<<endl;
                        User usr(id,username,password);
                        u.push_back(usr);
                        map[username]=id;
			currUser = usr;
			printProducts();
			//loginPage();	
		}
		void homePage(){
			system("clear");
			int choice;
			cout << "Welcome to Flipkart!"<<endl;
			cout << "1. Login" << endl;
			cout << "2. Signup" << endl;			
			cout << "Enter the number of your choice : " ;
			cin >> choice;
			system("clear");
			if(choice == 1){loginPage();return;}
			if(choice == 2){signupPage();return;}
			else cout << "Wrong choice, please try again!"<<endl;
			homePage();
			return;
		}
};

int main(){
	Flipkart f;
	int t;
	cout << "Enter the number of products you want to start with."<<endl;
	cin >> t;
	cin.ignore(1,'\n');
	while(t--)f.addProduct();
	f.homePage();
	return 0;
}

