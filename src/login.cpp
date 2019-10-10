#include <iostream>
#include "authlib.h"
#include <string>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
using namespace std;

/**
 * Source of hash function: 
 * https://stackoverflow.com/questions/13784434/how-to-use-openssls-sha256-functions#1378448
*/

string userName; 
string pswd; 

void usrInput(){
  cout<<"Enter your username"<<"Enter your password"<<endl;
  cin>>userName>>pswd; 

  sha256(pswd);


} 




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



int main()
{
  //bool auth = true;

  //if (auth) authenticated("user");
  //else rejected("user");
  usrInput
  cout << sha256() << endl;
}
