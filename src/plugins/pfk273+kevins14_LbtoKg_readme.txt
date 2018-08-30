┌─────────────────┬──────────────────────────────────────────────────────────┐
│ Title           │ lb and kg converter                                      │
├─────────────────┼──────────────────────────────────────────────────────────┤
│ Author(s)       │ Paul Kim (pfk273), Kevin Song (kevins14)                 │
├─────────────────┼──────────────────────────────────────────────────────────┤
│ Description     │ This plugin can convert lb to kg and kg to lb.           │
│                 │                                                          │
│                 │                                                          │
└─────────────────┴──────────────────────────────────────────────────────────┘

Full feature set:
  - To calculate the total calories, type 'lbtokg' followed by the unit and number sequencially.
  - Input 'lb' to convert the number to pound and 'kg' to convert the number to kilogram.

Other notes:
  - Error message: if put less arguments, "Need two arguments "
		if put the first argument is not matching with 'lb' or 'kg', "Put proper arguments "
Usage:
    Acceptable:

        esh> lbtokg lb 80
	176.4

	esh> lbtokg kg 150
	68.0

    Inacceptable:

	esh> lbtokg

	ehs> lbtokg kg

        esh> lbtokg lbs 232

	esh> lbtokg 23 lb
