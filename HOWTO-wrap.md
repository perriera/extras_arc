

## HOWTO-wrap.md
This utility combines the features of both the **parcel** and **implode** utilities. It essentially implodes a zip of certain types of files, (in this case image files) and then converts what is left into hexadecimal format, (for use with sockets).

## Wrap
The implode utility manages a hexadecimal version of a given binary file. 

	wrap <filename> [-wrap|-unwrap|-merge|-clean|-help]

The operations are placed at the end of the command as a convenience.

### -wrap <default>
> If no operation is specified then the **-wrap** operation is assumed.

	build/wrap data/exparx.webflow.zip -wrap

> In the same directory of the specified zip archive a stripped down archive is created and given a **_imploded.zip** extension.  

	/home/perry/Projects/extras_arc/data/exparx.webflow.zip
	/home/perry/Projects/extras_arc/data/exparx.webflow.zip_imploded.zip
	/home/perry/Projects/extras_arc/data/exparx.webflow.zip_imploded.zip_hexed.txt
	/home/perry/Projects/extras_arc/data/exparx.webflow.zip_imploded.zip_packed.txt

### -unwrap
> Provided a  **_imploded.zip_packed.zip** version of the original was created first, (and the original also exists in the same directory) then a **_exploded.zip** is created. 
> 
> 
		build/wrap data/exparx.webflow.zip -unwrap
		
> **Note:** It may not be the same size as the original zip as the zip compression algorithm on the original may be different than the one used by the implode utility.

	/home/perry/Projects/extras_arc/data/exparx.webflow.zip
	/home/perry/Projects/extras_arc/data/exparx.webflow.zip_exploded.zip
	/home/perry/Projects/extras_arc/data/exparx.webflow.zip_imploded.zip

### -merge
> This operation causes the **_exploded.zip** file to replace the original. It will also doubles as a **-clean** operation, removing any other files previous created by the implode utility, (for the specified filename).
> 
	build/wrap data/exparx.webflow.zip -merge 

> It will then list all the files of the same name, (which should be just one).

	/home/perry/Projects/extras_arc/data/exparx.webflow.zip

### -clean
> This operation will remove any other files previous created by the implode utility, (for the specified filename).
> 
	build/wrap data/exparx.webflow.zip -clean 

> It will then list all the files of the same name, (which should be just one).

	/home/perry/Projects/extras_arc/data/exparx.webflow.zipbui

### -help
> Displays this help text, (provided the file is in the same directory).

## Summary
This utility was put together as a convenience. It can be installed as part of the operating system, (see INSTALL.md).


 
