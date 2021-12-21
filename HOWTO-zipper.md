## HOWTO-zipper.md

This utility simplifies the process of preparing a source directory, (usually named the **src/** directory) for transport over a socket connection. It does this by zipping up the current contents then unzipping them again later. Simply deleting the current **src/** directory is not a good idea as it may cause confusion for a http server running locally for testing purposes. So, this utility is designed to work with **ng_monitor** such that then latest contents of the **src/** directory are required they can be zipped and unzipped quickly and easily using this particular command line utility.

## Zipper

This utility simplifies the process of preparing a source directory for transport over a socket connection

    zipper <filename> <dir> [-unzip|-rezip|-create|-append|-help]

The operations are placed at the end of the command as a convenience.

### -unzip <default>

> Unzips the contents of the zip file into a zip directory, (that does not currently exist). Use -append, (below) to unzip to a currently existing directory.

    build/zipper testit/src.zip  testit/ -unzjp

### -rezip <default>

> Updates an existing new zip file from the contents of the source directory, (**note**: the current version is not working as expected).

    build/zipper testit/src.zip  testit/ -rezjp

### -create <default>

> Creates a brand new zip file from the contents of the source directory.

    build/zipper testit/src.zip  testit/ -create

### -append <default>

> Unzips the zip archive into the source directory in a none-destructive manner, (such that the original source directory is not deleted first).

    build/zipper testit/src.zip  testit/ -append

### -help

> Displays this help text, (provided the file is in the same directory).

## Summary

This utility was put together as a convenience. It can be installed as part of the operating system, (see INSTALL.md).
