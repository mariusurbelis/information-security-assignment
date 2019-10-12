#include <iostream>
#include "authlib.h"
#include <string>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <string.h>
#include <fstream>
#include <vector>

using namespace std;

const string DB_FILE_NAME = "pwdb.txt";

vector<array<string, 2>> database;

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

// Takes in two string paramaters and compares them
// if both strings are the same, return true. If not, return false
bool passCompare(string user_input, string stored_pass)
{
  // variable x contains an number for the result of the comparison of the two strings
  // 0 = the same. else = not the same
  int x = user_input.compare(stored_pass);
  if (x == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}
/**
 *  db_parse_line function parses an input string
 *  which contains a username and password split
 *  using a colon ":". The username and password
 *  are stored inside a vector called database.
 * 
 *  @param line is the input string
*/
void db_parse_line(string line)
{
  istringstream tokenStream(line);
  vector<string> tokens;
  string token;

  while (getline(tokenStream, token, ':'))
    tokens.push_back(token);

  database.push_back({tokens[0], tokens[1]});
}

int import_cred_db(const string db_file_name)
{
  ifstream db_file(db_file_name);
  string db_line;
  if (db_file.is_open())
  {
    while (getline(db_file, db_line))
    {
      //cout << db_line<<endl;
      db_parse_line(db_line);
    }
    db_file.close();
  }
  else
  {
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

  usrInput();
  string a;
  cout << sha256(a) << endl;
}