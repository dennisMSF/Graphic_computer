//a_ulColor & 0xFF000000 --> 00000000 00000000 00000000 00000000
//a_ulColor & 0xFF0000   --> 00000000 10010011 00000000 00000000
//a_ulColor & 0x00FF00   --> 00000000 00000000 11001100 00000000
//a_ulColor & 0x0000FF   --> 00000000 00000000 00000000 11101010
#define HEX_COLOR(hex)                      \
    (double)(((hex) >> (3 * 8)) & 0xFF )/ 255,              \
    (double)(((hex) >> (2 * 8)) & 0xFF)/ 255,              \
    (double)(((hex) >> (1* 8)) & 0xFF )/ 255,              \
    (double)(((hex) >> (0 * 8)) & 0xFF) / 255
#define aliceblue 0xf0f8ffff 
#define antiquewhite  0xfaebd7ff
#define aqua  0x00ffffff
#define aquamarine  0x7fffd4ff
#define azure  0xf0ffffff
#define beige  0xf5f5dcff
#define bisque  0xffe4c4ff
#define black  0x000000ff
#define blanchedalmond  0xffebcdff
#define blue  0x0000ffff
#define blueviolet  0x8a2be2ff
#define brown  0xa52a2aff
#define burlywood  0xdeb887ff
#define cadetblue  0x5f9ea0ff
#define chartreuse  0x7fff00ff
#define chocolate  0xd2691eff
#define coral  0xff7f50ff
#define cornflowerblue  0x6495edff
#define cornsilk  0xfff8dcff
#define crimson  0xdc143cff
#define cyan  0x00ffffff
#define darkblue  0x00008bff
#define darkcyan  0x008b8bff
#define darkgoldenrod  0xb8860bff
#define darkgray  0xa9a9a9ff
#define darkgreen  0x006400ff
#define darkgrey  0xa9a9a9ff
#define darkkhaki  0xbdb76bff
#define darkmagenta  0x8b008bff
#define darkolivegreen  0x556b2fff
#define darkorange  0xff8c00ff
#define darkorchid  0x9932ccff
#define darkred  0x8b0000ff
#define darksalmon  0xe9967aff
#define darkseagreen  0x8fbc8fff
#define darkslateblue  0x483d8bff
#define darkslategray  0x2f4f4fff
#define darkslategrey  0x2f4f4fff
#define darkturquoise  0x00ced1ff
#define darkviolet  0x9400d3ff
#define deeppink  0xff1493ff
#define deepskyblue  0x00bfffff
#define dimgray  0x696969ff
#define dimgrey  0x696969ff
#define dodgerblue  0x1e90ffff
#define firebrick  0xb22222ff
#define floralwhite  0xfffaf0ff
#define forestgreen  0x228b22ff
#define fuchsia  0xff00ffff
#define gainsboro  0xdcdcdcff
#define ghostwhite  0xf8f8ffff
#define gold  0xffd700ff
#define goldenrod  0xdaa520ff
#define gray  0x808080ff
#define green  0x008000ff
#define greenyellow  0xadff2fff
#define grey  0x808080ff
#define honeydew  0xf0fff0ff
#define hotpink  0xff69b4ff
#define indianred  0xcd5c5cff
#define indigo  0x4b0082ff
#define ivory  0xfffff0ff
#define khaki  0xf0e68cff
#define lavender  0xe6e6faff
#define lavenderblush  0xfff0f5ff
#define lawngreen  0x7cfc00ff
#define lemonchiffon  0xfffacdff
#define lightblue  0xadd8e6ff
#define lightcoral  0xf08080ff
#define lightcyan  0xe0ffffff
#define lightgoldenrodyellow  0xfafad2ff
#define lightgray  0xd3d3d3ff
#define lightgreen  0x90ee90ff
#define lightgrey  0xd3d3d3ff
#define lightpink  0xffb6c1ff
#define lightsalmon  0xffa07aff
#define lightseagreen  0x20b2aaff
#define lightskyblue  0x87cefaff
#define lightslategray  0x778899ff
#define lightslategrey  0x778899ff
#define lightsteelblue  0xb0c4deff
#define lightyellow  0xffffe0ff
#define lime  0x00ff00ff
#define limegreen  0x32cd32ff
#define linen  0xfaf0e6ff
#define magenta  0xff00ffff
#define maroon  0x800000ff
#define mediumaquamarine  0x66cdaaff
#define mediumblue  0x0000cdff
#define mediumorchid  0xba55d3ff
#define mediumpurple  0x9370dbff
#define mediumseagreen  0x3cb371ff
#define mediumslateblue  0x7b68eeff
#define mediumspringgreen  0x00fa9aff
#define mediumturquoise  0x48d1ccff
#define mediumvioletred  0xc71585ff
#define midnightblue  0x191970ff
#define mintcream  0xf5fffaff
#define mistyrose  0xffe4e1ff
#define moccasin  0xffe4b5ff
#define navajowhite  0xffdeadff
#define navy  0x000080ff
#define oldlace  0xfdf5e6ff
#define olive  0x808000ff
#define olivedrab  0x6b8e23ff
#define orange  0xffa500ff
#define orangered  0xff4500ff
#define orchid  0xda70d6ff
#define palegoldenrod  0xeee8aaff
#define palegreen  0x98fb98ff
#define paleturquoise  0xafeeeeff
#define palevioletred  0xdb7093ff
#define papayawhip  0xffefd5ff
#define peachpuff  0xffdab9ff
#define peru  0xcd853fff
#define pink  0xffc0cbff
#define plum  0xdda0ddff
#define powderblue  0xb0e0e6ff
#define purple  0x800080ff
#define red  0xff0000ff
#define rosybrown  0xbc8f8fff
#define royalblue  0x4169e1ff
#define saddlebrown  0x8b4513ff
#define salmon  0xfa8072ff
#define sandybrown  0xf4a460ff
#define seagreen  0x2e8b57ff
#define seashell  0xfff5eeff
#define sienna  0xa0522dff
#define silver  0xc0c0c0ff
#define skyblue  0x87ceebff
#define slateblue  0x6a5acdff
#define slategray  0x708090ff
#define slategrey  0x708090ff
#define snow  0xfffafaff
#define springgreen  0x00ff7fff
#define steelblue  0x4682b4ff
#define tangerine  0xd2b48cff
#define teal  0x008080ff
#define thistle  0xd8bfd8ff
#define tomato  0xff6347ff
#define turquoise  0x40e0d0ff
#define violet  0xee82eeff
#define wheat  0xf5deb3ff
#define white  0xffffffff
#define whitesmoke  0xf5f5f5ff
#define yellow  0xffff00ff
#define yellowgreen  0x9acd32ff