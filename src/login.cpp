#include <iostream>
#include "authlib.h"
#include <string>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <string.h>
using namespace std;
// Function declaration 
  
/**
 * Source of hash function: 
 * https://stackoverflow.com/questions/13784434/how-to-use-openssls-sha256-functions#1378448
*/

string sha256(const string str)
{
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, str.c_str(), str.size());
  SHA256_Final(hash, &sha256);
  stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
  {
    ss << hex << setw(2) << setfill('0') << (int)hash[i];
  }
  return ss.str();
}

string userName; 
string psswd; 

/**
 *Function that fulfils the role of interacting with user by taking user input 
 */
void usrInput(){

    cout<<"Enter your username"<<endl;
    cin>>userName;

    cout<<"Enter your password"<<endl;
    cin>>psswd;

    sha256(psswd);


} 



int main()
{
  //bool auth = true;

  //if (auth) authenticated("user");
  //else rejected("user");
  usrInput();
  string a;
  cout << sha256(a) << endl;
}

