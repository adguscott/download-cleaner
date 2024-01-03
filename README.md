## Download Cleaner
### A program to clean up your download folder by moving files to their specified folders as configured in `config.h`
#### Why?
This project is a _my first_ C project. I needed a basic project, with small scope to sink my teeth into, and start putting what I've learnt into practise. 

### Configuration
Open the `config.h` file and modify the following variables:
* `downloaddir` needs to point to your Downloads directory
* The `dirtypes` array is an array of the `DirType` struct, specified in the `common.h` file.
    * The `DirType` struct has two fields, `dir` which a string which points to folder, and `types` which is a `string` array of file types associated with the `dir` folder.

