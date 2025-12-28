This is a small program, I've written to help me compare 2 files related to an issue I've had. I thought, I could share this, just in-case someone needs it.

## Usage

**THIS IS A CONSOLE APPLICATION, AND THUS REQUIRES TO BE OPEN WITH SOME KIND OF COMMAND LINE.**

- Download the latest version under the releases section.
- Then simply extract the .DLL and drop it in your games folder.
- Use with CMD, a Shell script, or anything else, that can be used for console applications.

**Commands:**\
   \
   While the naming might be a bit confusing, the explanation should clearly explain what it does.
   - `-file_a` is used to specify the **first** file to use in the comparison. (REQUIRED)
   - `-file_b` is used to specify the **second** file to use in the comparison. (REQUIRED)
   - `-skip_byte_size` is used to bypass the check on "if the size of both files doesn't match". Useful if you need to compare bytes despite the files having different sizes. (OPTIONAL)
   - `-print_all` is used to print every single byte, that doesn't match instead of stopping on the first non-match. (OPTIONAL)

## Make your own version

1. You should be able to either press the green button saying "Code" and press Download ZIP. Obviously a different way if you have your own.
2. After that you normally extract the files, and voilà! You have successfully cloned the project.
3. Open the .sln file using Visual Studio (Latest recommended).
4. Once you have made your changes and are ready to test, then just simply go to "Build" on top of the window and either click "Build Source" or "Build Solution". Both options are completely same, unless you have changed them yourself, which I assume you know the difference if you do.
5. If the build was successful, then in the location where your .sln file is, you now have a new folder called "Compiled". Open it, then folder "Files" and there's your .exe, which you can now put into your games folder!

## License

This project is licensed under the [MIT License](https://choosealicense.com/licenses/mit/).
