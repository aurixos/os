# Soapine configuration
To work and do what you told it to do, Soapine uses a configuration file.

## Location
Soapine will search for the configuration in:
* `(boot partition)\soapine.cfg`
* `(boot partition)\soapine\soapine.cfg`
* `(boot partition)\EFI\BOOT\soapine.cfg`
* `(boot partition)\EFI\soapine.cfg`

If Soapine finds the config file, he parses it and jump to his usual menu. Else, Soapine will display a stop screen saying that you need to fix your configuration

## Accepted value types
* String literal (`"Hello, World!"`)
* Decimal (`2`)
* Hexadecimal (`0x2`)
* Hexadecimal color (`#FFFFFF`)
* Boolean (`true/false`)

## Declarations
Declarations are values that components of Soapine will search for:
If you declare `VERBOSE` with a value of true, Soapine will itself put in verbose mode.

You can do a declaration by writing the name + an equal sign + the value (using the accepted value types), that will make `NAME=VALUE`.

If an unused declaration is provided (for example `FORCE_SOAPINE_TO_LIKE_ME=true`), Soapine will simply ignore it, but it will still be present.

Here are some example declarations:
* `MENU_BRANDING="Raphaël's Custom Soapine!!"` (string literal)
* `MENU_HEADERBAR_BG=#FFFFFF` (Hexadecimal color)
* `MENU_HEADERBAR_MARGIN=1` (decimal)
* `VERBOSE=true` (boolean)
* `LOAD_ADDRESS=0x1000` (hexadecimal)

## Menu entries
Menu entries allow you to show an operating system (that can be loaded with the supported protocols!) on the menu.
They are declared like that:

```c
menu_entry "Project Jupiter" {

};
```
*(yes i decided to give a C-like syntax to it)*

You can put a small number of declarations inside the menu entries. (PROTOCOL, IMAGE_PATH, CMDLINE, RESOLUTION) (Providing the `PROTOCOL` and `IMAGE_PATH` declarations is required for Soapine to boot your OS!)

## Supported declarations
None for now (we just got the config parser working!)

At least, you can still define entries!