## Download Cleaner
### A program to clean up your download folder by moving files to their specified folders configured in `config.h`
#### Why?
This project was intended as a first **C** project to start putting my study into practice. I hope to look back on this and see how far I've come, and use it as a stepping stone to improve my skills.

### Configuration
Open the `config.h` file and modify the following variables:
* `downloaddir` needs to point to your Downloads directory
* The `dirtypes` array is an array of the `DirType` struct, specified in the `common.h` file.
    * The `DirType` struct has two fields, `dir`, a `string` to assign the path of a folder, and `types` which is a `string` array of the file types associated with this folder.



