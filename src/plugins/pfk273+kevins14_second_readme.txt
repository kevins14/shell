┌─────────────────┬──────────────────────────────────────────────────────────┐
│ Title           │ Second converter                                         │
├─────────────────┼──────────────────────────────────────────────────────────┤
│ Author(s)       │ Paul Kim (pfk273), Kevin Song (kevins14)                 │
├─────────────────┼──────────────────────────────────────────────────────────┤
│ Description     │ This plugin can convert seconds to day, hour, minute,    │
│                 │ second.                                                  │
│                 │                                                          │
└─────────────────┴──────────────────────────────────────────────────────────┘

Full feature set:
  - To calculate the total calories, type 'second' followed by the second.

Other notes:
  - Error message: if put no argument, "Need an argument "

Usage:
    Acceptable:

        esh> second 10000
	10000sec is 0day 2hour 46min 40sec.

	esh> second 123456
	123456sec is 1day 10hour 17min 36sec.

    Inacceptable:

	esh> second
