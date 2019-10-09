# Information Security Assignment

### General TODO (login procedure)
- Read from the passwords db file
  - Parse for the pass and username
  - ~~Can use a data structure to store the username and hashed pass~~
- Some form of an interface
  - Just a CMD interface
  - Which takes in the user input
    - For username and password
- Hashing function which uses OpenSSL
  - ```string hash_pass(string paintext_pass)```
  - Compairing the hashed pass to the db pass and determine if its authenticated or rejected
