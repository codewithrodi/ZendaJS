const Code = `
# With ZendaJS you can integrate Python in your
# JavaScript programs!

# This is a example simple usage

MESSAGE = str(input('Enter a message: '))

print(f'''

Your message is {MESSAGE} and it contains {len(MESSAGE)} characteres!

''')
`;

// Calling the pythonString function for execute code
PythonString(Code);

// Calling Python File
PythonFile('examples/PyIntegrationExample.py')

// You need enter exact python file location :)

// Use pythonFancyFile for get better perfomance, u need python in your OS.
PythonFancyFile('examples/PyIntegrationExample.py')