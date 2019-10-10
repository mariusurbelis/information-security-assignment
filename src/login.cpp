#include <iostream>
#include "authlib.h"
#include <string>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <fstream>

using namespace std;

const string DB_FILE_NAME = "pwdb.txt;

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

int import_cred_db(const string db_file_name){
  ifstream db_file(db_file_name);
  string db_line;
  if(db_file.is_open()){
    while (getline(db_file,db_line)){
      //cout << db_line<<endl;
      db_parse_line(db_line);
    }
    db_file.close();
  } else {
    cout << "Unable to read password db file" << endl;
    return 1;
  }
  return 0;
}

int main()
{
  import_cred_db(DB_FILE_NAME);
  //bool auth = true;

  //if (auth) authenticated("user");
  //else rejected("user");

  //cout << sha256("TEST") << endl;
}
