
OUTNAME = 'webpage.hpp'
INNAME = 'page.html'
TEMPLATE = '''const char INDEX[] = R"""(
{}
)""";
'''

with open(INNAME) as f:
    webpage = f.read()
with open(OUTNAME, 'w') as f:
    f.write(TEMPLATE.format(webpage))
