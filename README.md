## Download Cleaner
### A program to clean up your download folder by moving files to their specified folders configured in `config.h`
This project was intended as a simple, first **C** project to start putting my study into practice.

### Configuration
Open the `config.h` file and modify the following variables:
* `downloaddir` needs to point to your Downloads directory
* The `dirtypes` array is an array of the `DirType` struct, specified in the `common.h` file.
    * The `DirType` struct has two fields, `dir`, a `string` to assign the path of a folder, and `types` which is a comma delimited `string` containing the file types associated with this folder.



