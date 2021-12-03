## HOWTO-parcel.md
This package provides a convenient method of converting a binary into it's hexadecimal equivalent. This is ideal for managing files over a socket connection as more often than not issues arise with sending/receiving pure binary files over a socket connection. By converting to text/hexadecimal format first, a lot of errors can be isolated but being able to see just what is transpiring over a socket connection. There maybe other applications for this utility as well. 

## Parcel
The parcel utility manages a hexadecimal version of a given binary file. 

	parcel <filename> [-pack|-unpack|-verify|-clean|-unzip|-merge|-help] 

The operations are placed at the end of the command as a convenience.

### -pack
> This parameter creates a hexadecimal version of a given binary file. 

	build/parcel data/exparx.webflow.zip -pack 

> In the same directory that the file exists two more files will be created:      

	data/exparx.webflow.zip
	data/exparx.webflow.zip_packed.txt
	data/exparx.webflow.zip_hexed.txt   

### -cat
> To see the content of the packed file you can use the -cat parameter

	build/parcel data/exparx.webflow.zip -cat
Only the contents of the **_packed.txt** are displayed


	 : 1 / 11072 : 504b03040a0000000000d9866153000000000000000000000000040000006373732f504b03040a00 : 243d
	 : 2 / 11072 : 00000000d9866153570e66405c1e00005c1e0000110000006373732f6e6f726d616c697a652e6373 : 11d1
	 : 3 / 11072 : 732f2a21206e6f726d616c697a652e6373732076332e302e33207c204d4954204c6963656e736520 : 3b27
	 : 4 / 11072 : 7c206769746875622e636f6d2f6e65636f6c61732f6e6f726d616c697a652e637373202a2f0a2f2a : e3c
	 : 5 / 11072 : 2a0a202a20312e205365742064656661756c7420666f6e742066616d696c7920746f2073616e732d : a5e1
	 : 6 / 11072 : 73657269662e0a202a20322e2050726576656e7420694f5320616e6420494520746578742073697a : dbe7
	 : 7 / 11072 : 652061646a75737420616674657220646576696365206f7269656e746174696f6e206368616e6765 : 7804

### -unpack
> To convert the **_packed.txt** file back into it's original binary format:

	build/parcel data/exparx.webflow.zip -unpack

Results in:

	data/exparx.webflow.zip_packed.txt
	data/exparx.webflow.zip_duplicate.bin

As a precaution the original file is not overwritten, (to do that use the -merge command below)

### -verify
> To make sure the duplicate and the original are identical use the -verify option

	build/parcel data/exparx.webflow.zip -verify

Results in:

	No differences detected
	data/exparx.webflow.zip_packed.txt
	data/exparx.webflow.zip_duplicate.bin

### -merge
> This operation will remove the original and replace it with the duplicate.

	build/parcel data/exparx.webflow.zip -merge

Results in:

	build/parcel data/exparx.webflow.zip

### -clean
> This operation will remove the hex, packed and duplicate versions of the original.

	build/parcel data/exparx.webflow.zip -clean

Results in:

	build/parcel data/exparx.webflow.zip

### -unzip
> This operation will unzip the contents of the duplicate file but do it into the /tmp directory. It's purpose is just to save you a step when making sure that the file was sent over the socket that it arrived as expected.

	build/parcel data/exparx.webflow.zip -unzip

Results in:

	 creating: /tmp/css/
	 extracting: /tmp/css/normalize.css  
	 extracting: /tmp/css/webflow.css    
	 extracting: /tmp/css/exparx.webflow.css  
	 creating: /tmp/js/
	 extracting: /tmp/js/webflow.js   
	  etc etc ...  

### -help
> Displays this help text, (provided this file is in the same directory).

## Summary
This utility was put together as a convenience. It can be installed as part of the operating system, (see INSTALL.md).


 
