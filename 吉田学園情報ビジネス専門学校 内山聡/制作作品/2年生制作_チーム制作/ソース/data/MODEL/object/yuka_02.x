xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 138;
 -114.56354;17.42072;114.56354;,
 114.56354;17.42072;114.56354;,
 114.56354;17.42072;-114.56354;,
 -114.56354;17.42072;-114.56354;,
 -114.56354;14.74089;-143.20441;,
 114.56354;14.74089;-143.20441;,
 114.56354;-6.69772;-143.20441;,
 -114.56354;-6.69772;-143.20441;,
 -114.56354;-9.37753;-114.56354;,
 114.56354;-9.37753;-114.56354;,
 114.56354;-9.37753;114.56354;,
 -114.56354;-9.37753;114.56354;,
 -114.56354;-6.69772;143.20441;,
 114.56354;-6.69772;143.20441;,
 114.56354;14.74089;143.20441;,
 -114.56354;14.74089;143.20441;,
 143.20441;14.74089;114.56354;,
 143.20441;-6.69772;114.56354;,
 143.20441;-6.69772;-114.56354;,
 143.20441;14.74089;-114.56354;,
 -143.20441;-6.69772;114.56354;,
 -143.20441;14.74089;114.56354;,
 -143.20441;14.74089;-114.56354;,
 -143.20441;-6.69772;-114.56354;,
 -114.56354;17.42072;-114.56354;,
 114.56354;17.42072;-114.56354;,
 114.56354;17.21677;-125.52397;,
 -114.56354;17.21677;-125.52397;,
 114.56354;16.63585;-134.81573;,
 -114.56354;16.63585;-134.81573;,
 114.56354;15.76642;-141.02428;,
 -114.56354;15.76642;-141.02428;,
 114.56354;14.74089;-143.20441;,
 -114.56354;-9.17355;-125.52397;,
 114.56354;-9.17355;-125.52397;,
 114.56354;-9.37753;-114.56354;,
 -114.56354;-8.59265;-134.81573;,
 114.56354;-8.59265;-134.81573;,
 -114.56354;-7.72327;-141.02428;,
 114.56354;-7.72327;-141.02428;,
 -114.56354;-6.69772;-143.20441;,
 114.56354;-6.69772;-143.20441;,
 -114.56354;17.21677;125.52397;,
 114.56354;17.21677;125.52397;,
 114.56354;17.42072;114.56354;,
 -114.56354;16.63585;134.81573;,
 114.56354;16.63585;134.81573;,
 -114.56354;15.76642;141.02428;,
 114.56354;15.76642;141.02428;,
 -114.56354;14.74089;143.20441;,
 114.56354;14.74089;143.20441;,
 -114.56354;-9.37753;114.56354;,
 114.56354;-9.37753;114.56354;,
 114.56354;-9.17355;125.52397;,
 -114.56354;-9.17355;125.52397;,
 114.56354;-8.59265;134.81573;,
 -114.56354;-8.59265;134.81573;,
 114.56354;-7.72327;141.02428;,
 -114.56354;-7.72327;141.02428;,
 114.56354;-6.69772;143.20441;,
 125.52397;17.21677;114.56354;,
 125.52397;17.21677;-114.56354;,
 134.81573;16.63585;114.56354;,
 134.81573;16.63585;-114.56354;,
 141.02428;15.76642;114.56354;,
 141.02428;15.76642;-114.56354;,
 143.20441;14.74089;-114.56354;,
 125.52397;-9.17355;-114.56354;,
 125.52397;-9.17355;114.56354;,
 134.81573;-8.59265;-114.56354;,
 134.81573;-8.59265;114.56354;,
 141.02428;-7.72327;-114.56354;,
 141.02428;-7.72327;114.56354;,
 143.20441;-6.69772;-114.56354;,
 143.20441;-6.69772;114.56354;,
 -125.52397;17.21677;-114.56354;,
 -125.52397;17.21677;114.56354;,
 -134.81573;16.63585;-114.56354;,
 -134.81573;16.63585;114.56354;,
 -141.02428;15.76642;-114.56354;,
 -141.02428;15.76642;114.56354;,
 -143.20441;14.74089;-114.56354;,
 -143.20441;14.74089;114.56354;,
 -125.52397;-9.17355;114.56354;,
 -125.52397;-9.17355;-114.56354;,
 -134.81573;-8.59265;114.56354;,
 -134.81573;-8.59265;-114.56354;,
 -141.02428;-7.72327;114.56354;,
 -141.02428;-7.72327;-114.56354;,
 -143.20441;-6.69772;-114.56354;,
 125.52397;14.74089;-141.02428;,
 125.52397;-6.69772;-141.02428;,
 134.81573;14.74089;-134.81573;,
 134.81573;-6.69772;-134.81573;,
 141.02428;14.74089;-125.52397;,
 141.02428;-6.69772;-125.52397;,
 125.52397;-6.69772;141.02428;,
 125.52397;14.74089;141.02428;,
 134.81573;-6.69772;134.81573;,
 134.81573;14.74089;134.81573;,
 141.02428;-6.69772;125.52397;,
 141.02428;14.74089;125.52397;,
 -125.52397;-6.69772;-141.02428;,
 -125.52397;14.74089;-141.02428;,
 -134.81573;-6.69772;-134.81573;,
 -134.81573;14.74089;-134.81573;,
 -141.02428;-6.69772;-125.52397;,
 -141.02428;14.74089;-125.52397;,
 -125.52397;14.74089;141.02428;,
 -125.52397;-6.69772;141.02428;,
 -134.81573;14.74089;134.81573;,
 -134.81573;-6.69772;134.81573;,
 -141.02428;14.74089;125.52397;,
 -141.02428;-6.69772;125.52397;,
 128.88397;16.63585;-128.88397;,
 137.47922;15.76642;-127.79388;,
 127.79388;15.76642;-137.47922;,
 -128.88397;16.63585;-128.88397;,
 -137.47922;15.76642;-127.79388;,
 -127.79388;15.76642;-137.47922;,
 128.88397;-8.59265;-128.88397;,
 137.47922;-7.72327;-127.79388;,
 127.79388;-7.72327;-137.47922;,
 128.88397;16.63585;128.88397;,
 137.47922;15.76642;127.79388;,
 127.79388;15.76642;137.47922;,
 -128.88397;-8.59265;-128.88397;,
 -137.47922;-7.72327;-127.79388;,
 -127.79388;-7.72327;-137.47922;,
 128.88397;-8.59265;128.88397;,
 137.47922;-7.72327;127.79388;,
 127.79388;-7.72327;137.47922;,
 -128.88397;16.63585;128.88397;,
 -137.47922;15.76642;127.79388;,
 -127.79388;15.76642;137.47922;,
 -128.88397;-8.59265;128.88397;,
 -137.47922;-7.72327;127.79388;,
 -127.79388;-7.72327;137.47922;;
 
 182;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;27,26,28,29;,
 4;29,28,30,31;,
 4;31,30,32,4;,
 4;33,34,35,8;,
 4;36,37,34,33;,
 4;38,39,37,36;,
 4;40,41,39,38;,
 4;42,43,44,0;,
 4;45,46,43,42;,
 4;47,48,46,45;,
 4;49,50,48,47;,
 4;51,52,53,54;,
 4;54,53,55,56;,
 4;56,55,57,58;,
 4;58,57,59,12;,
 4;25,44,60,61;,
 4;61,60,62,63;,
 4;63,62,64,65;,
 4;65,64,16,66;,
 4;52,35,67,68;,
 4;68,67,69,70;,
 4;70,69,71,72;,
 4;72,71,73,74;,
 4;0,24,75,76;,
 4;76,75,77,78;,
 4;78,77,79,80;,
 4;80,79,81,82;,
 4;8,51,83,84;,
 4;84,83,85,86;,
 4;86,85,87,88;,
 4;88,87,20,89;,
 4;41,32,90,91;,
 4;91,90,92,93;,
 4;93,92,94,95;,
 4;95,94,66,73;,
 4;50,59,96,97;,
 4;97,96,98,99;,
 4;99,98,100,101;,
 4;101,100,74,16;,
 4;4,40,102,103;,
 4;103,102,104,105;,
 4;105,104,106,107;,
 4;107,106,89,81;,
 4;12,49,108,109;,
 4;109,108,110,111;,
 4;111,110,112,113;,
 4;113,112,82,20;,
 3;25,61,26;,
 3;61,63,114;,
 3;114,26,61;,
 3;26,114,28;,
 3;63,65,115;,
 3;115,114,63;,
 3;114,115,116;,
 3;116,28,114;,
 3;28,116,30;,
 3;65,66,94;,
 3;94,115,65;,
 3;115,94,92;,
 3;92,116,115;,
 3;116,92,90;,
 3;90,30,116;,
 3;30,90,32;,
 3;27,75,24;,
 3;117,77,75;,
 3;75,27,117;,
 3;29,117,27;,
 3;118,79,77;,
 3;77,117,118;,
 3;119,118,117;,
 3;117,29,119;,
 3;31,119,29;,
 3;107,81,79;,
 3;79,118,107;,
 3;105,107,118;,
 3;118,119,105;,
 3;103,105,119;,
 3;119,31,103;,
 3;4,103,31;,
 3;34,67,35;,
 3;120,69,67;,
 3;67,34,120;,
 3;37,120,34;,
 3;121,71,69;,
 3;69,120,121;,
 3;122,121,120;,
 3;120,37,122;,
 3;39,122,37;,
 3;95,73,71;,
 3;71,121,95;,
 3;93,95,121;,
 3;121,122,93;,
 3;91,93,122;,
 3;122,39,91;,
 3;41,91,39;,
 3;43,60,44;,
 3;123,62,60;,
 3;60,43,123;,
 3;46,123,43;,
 3;124,64,62;,
 3;62,123,124;,
 3;125,124,123;,
 3;123,46,125;,
 3;48,125,46;,
 3;101,16,64;,
 3;64,124,101;,
 3;99,101,124;,
 3;124,125,99;,
 3;97,99,125;,
 3;125,48,97;,
 3;50,97,48;,
 3;8,84,33;,
 3;84,86,126;,
 3;126,33,84;,
 3;33,126,36;,
 3;86,88,127;,
 3;127,126,86;,
 3;126,127,128;,
 3;128,36,126;,
 3;36,128,38;,
 3;88,89,106;,
 3;106,127,88;,
 3;127,106,104;,
 3;104,128,127;,
 3;128,104,102;,
 3;102,38,128;,
 3;38,102,40;,
 3;52,68,53;,
 3;68,70,129;,
 3;129,53,68;,
 3;53,129,55;,
 3;70,72,130;,
 3;130,129,70;,
 3;129,130,131;,
 3;131,55,129;,
 3;55,131,57;,
 3;72,74,100;,
 3;100,130,72;,
 3;130,100,98;,
 3;98,131,130;,
 3;131,98,96;,
 3;96,57,131;,
 3;57,96,59;,
 3;0,76,42;,
 3;76,78,132;,
 3;132,42,76;,
 3;42,132,45;,
 3;78,80,133;,
 3;133,132,78;,
 3;132,133,134;,
 3;134,45,132;,
 3;45,134,47;,
 3;80,82,112;,
 3;112,133,80;,
 3;133,112,110;,
 3;110,134,133;,
 3;134,110,108;,
 3;108,47,134;,
 3;47,108,49;,
 3;54,83,51;,
 3;135,85,83;,
 3;83,54,135;,
 3;56,135,54;,
 3;136,87,85;,
 3;85,135,136;,
 3;137,136,135;,
 3;135,56,137;,
 3;58,137,56;,
 3;113,20,87;,
 3;87,136,113;,
 3;111,113,136;,
 3;136,137,111;,
 3;109,111,137;,
 3;137,58,109;,
 3;12,109,58;;
 
 MeshMaterialList {
  2;
  182;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\COMMON\\OBJECT\\af18.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\COMMON\\OBJECT\\BreakBlock.jpg";
   }
  }
 }
 MeshNormals {
  136;
  -0.009302;0.999914;0.009302;,
  0.009302;0.999914;0.009302;,
  -0.009302;0.999914;-0.009302;,
  0.009302;0.999914;-0.009302;,
  -0.098016;0.000000;-0.995185;,
  0.098016;0.000000;-0.995185;,
  -0.009304;-0.999913;-0.009304;,
  0.009304;-0.999913;-0.009304;,
  -0.009304;-0.999913;0.009304;,
  0.009304;-0.999913;0.009304;,
  -0.098016;0.000000;0.995185;,
  0.098016;0.000000;0.995185;,
  0.995185;0.000000;0.098016;,
  0.995185;0.000000;-0.098016;,
  -0.995185;0.000000;0.098016;,
  -0.995185;0.000000;-0.098016;,
  -0.015456;0.999121;-0.038971;,
  0.015456;0.999121;-0.038971;,
  -0.021397;0.994585;-0.101698;,
  0.021397;0.994585;-0.101698;,
  -0.042318;0.954865;-0.294009;,
  0.042318;0.954865;-0.294009;,
  -0.015457;-0.999121;-0.038972;,
  0.015457;-0.999121;-0.038972;,
  -0.021396;-0.994586;-0.101693;,
  0.021396;-0.994586;-0.101693;,
  -0.042318;-0.954865;-0.294009;,
  0.042318;-0.954865;-0.294009;,
  -0.015456;0.999121;0.038971;,
  0.015456;0.999121;0.038971;,
  -0.021397;0.994585;0.101698;,
  0.021397;0.994585;0.101698;,
  -0.042318;0.954865;0.294009;,
  0.042318;0.954865;0.294009;,
  -0.015457;-0.999121;0.038972;,
  0.015457;-0.999121;0.038972;,
  -0.021396;-0.994586;0.101693;,
  0.021396;-0.994586;0.101693;,
  -0.042318;-0.954865;0.294009;,
  0.042318;-0.954865;0.294009;,
  0.038971;0.999121;0.015456;,
  0.038971;0.999121;-0.015456;,
  0.101698;0.994585;0.021397;,
  0.101698;0.994585;-0.021397;,
  0.294009;0.954865;0.042318;,
  0.294009;0.954865;-0.042318;,
  0.038972;-0.999121;0.015457;,
  0.038972;-0.999121;-0.015457;,
  0.101693;-0.994586;0.021396;,
  0.101693;-0.994586;-0.021396;,
  0.294009;-0.954865;0.042318;,
  0.294009;-0.954865;-0.042318;,
  -0.038971;0.999121;0.015456;,
  -0.038971;0.999121;-0.015456;,
  -0.101698;0.994585;0.021397;,
  -0.101698;0.994585;-0.021397;,
  -0.294009;0.954865;0.042318;,
  -0.294009;0.954865;-0.042318;,
  -0.038972;-0.999121;0.015457;,
  -0.038972;-0.999121;-0.015457;,
  -0.101693;-0.994586;0.021396;,
  -0.101693;-0.994586;-0.021396;,
  -0.294009;-0.954865;0.042318;,
  -0.294009;-0.954865;-0.042318;,
  0.287840;-0.640574;-0.711908;,
  0.287839;0.640577;-0.711906;,
  0.550482;-0.627645;-0.550482;,
  0.550480;0.627648;-0.550480;,
  0.857680;-0.326535;-0.397190;,
  0.857680;0.326537;-0.397189;,
  0.287840;-0.640574;0.711908;,
  0.287839;0.640577;0.711906;,
  0.550482;-0.627645;0.550482;,
  0.550480;0.627648;0.550480;,
  0.857680;-0.326535;0.397190;,
  0.857680;0.326537;0.397189;,
  -0.287840;-0.640574;-0.711908;,
  -0.287839;0.640577;-0.711906;,
  -0.550482;-0.627645;-0.550482;,
  -0.550480;0.627648;-0.550480;,
  -0.857680;-0.326535;-0.397190;,
  -0.857680;0.326537;-0.397189;,
  -0.287840;-0.640574;0.711908;,
  -0.287839;0.640577;0.711906;,
  -0.550482;-0.627645;0.550482;,
  -0.550480;0.627648;0.550480;,
  -0.857680;-0.326535;0.397190;,
  -0.857680;0.326537;0.397189;,
  0.064301;0.995857;-0.064301;,
  0.226684;0.964668;-0.134275;,
  0.134275;0.964668;-0.226684;,
  -0.064301;0.995857;-0.064301;,
  -0.226684;0.964668;-0.134275;,
  -0.134275;0.964668;-0.226684;,
  0.064298;-0.995857;-0.064298;,
  0.226683;-0.964668;-0.134275;,
  0.134275;-0.964668;-0.226683;,
  0.064301;0.995857;0.064301;,
  0.226684;0.964668;0.134275;,
  0.134275;0.964668;0.226684;,
  -0.064298;-0.995857;-0.064298;,
  -0.226683;-0.964668;-0.134275;,
  -0.134275;-0.964668;-0.226683;,
  0.064298;-0.995857;0.064298;,
  0.226683;-0.964668;0.134275;,
  0.134275;-0.964668;0.226683;,
  -0.064301;0.995857;0.064301;,
  -0.226684;0.964668;0.134275;,
  -0.134275;0.964668;0.226684;,
  -0.064298;-0.995857;0.064298;,
  -0.226683;-0.964668;0.134275;,
  -0.134275;-0.964668;0.226683;,
  0.042220;0.904078;-0.425276;,
  -0.042220;0.904078;-0.425276;,
  -0.042221;-0.904076;-0.425281;,
  0.042221;-0.904076;-0.425281;,
  -0.042220;0.904078;0.425276;,
  0.042220;0.904078;0.425276;,
  0.042221;-0.904076;0.425281;,
  -0.042221;-0.904076;0.425281;,
  0.425276;0.904078;0.042220;,
  0.425276;0.904078;-0.042220;,
  0.425281;-0.904076;-0.042221;,
  0.425281;-0.904076;0.042221;,
  -0.425276;0.904078;-0.042220;,
  -0.425276;0.904078;0.042220;,
  -0.425281;-0.904076;0.042221;,
  -0.425281;-0.904076;-0.042221;,
  0.376770;0.922279;-0.086294;,
  -0.376770;0.922279;-0.086294;,
  0.376774;-0.922277;-0.086295;,
  0.376770;0.922279;0.086294;,
  -0.376774;-0.922277;-0.086295;,
  0.376774;-0.922277;0.086295;,
  -0.376770;0.922279;0.086294;,
  -0.376774;-0.922277;0.086295;;
  182;
  4;0,1,3,2;,
  4;4,5,5,4;,
  4;6,7,9,8;,
  4;10,11,11,10;,
  4;12,12,13,13;,
  4;14,14,15,15;,
  4;2,3,17,16;,
  4;16,17,19,18;,
  4;18,19,21,20;,
  4;20,21,112,113;,
  4;22,23,7,6;,
  4;24,25,23,22;,
  4;26,27,25,24;,
  4;114,115,27,26;,
  4;28,29,1,0;,
  4;30,31,29,28;,
  4;32,33,31,30;,
  4;116,117,33,32;,
  4;8,9,35,34;,
  4;34,35,37,36;,
  4;36,37,39,38;,
  4;38,39,118,119;,
  4;3,1,40,41;,
  4;41,40,42,43;,
  4;43,42,44,45;,
  4;45,44,120,121;,
  4;9,7,47,46;,
  4;46,47,49,48;,
  4;48,49,51,50;,
  4;50,51,122,123;,
  4;0,2,53,52;,
  4;52,53,55,54;,
  4;54,55,57,56;,
  4;56,57,124,125;,
  4;6,8,58,59;,
  4;59,58,60,61;,
  4;61,60,62,63;,
  4;63,62,126,127;,
  4;5,5,65,64;,
  4;64,65,67,66;,
  4;66,67,69,68;,
  4;68,69,13,13;,
  4;11,11,70,71;,
  4;71,70,72,73;,
  4;73,72,74,75;,
  4;75,74,12,12;,
  4;4,4,76,77;,
  4;77,76,78,79;,
  4;79,78,80,81;,
  4;81,80,15,15;,
  4;10,10,83,82;,
  4;82,83,85,84;,
  4;84,85,87,86;,
  4;86,87,14,14;,
  3;3,41,17;,
  3;41,43,88;,
  3;88,17,41;,
  3;17,88,19;,
  3;43,45,89;,
  3;89,88,43;,
  3;88,89,90;,
  3;90,19,88;,
  3;19,90,21;,
  3;45,121,128;,
  3;128,89,45;,
  3;89,69,67;,
  3;67,90,89;,
  3;90,67,65;,
  3;65,21,90;,
  3;21,65,112;,
  3;16,53,2;,
  3;91,55,53;,
  3;53,16,91;,
  3;18,91,16;,
  3;92,57,55;,
  3;55,91,92;,
  3;93,92,91;,
  3;91,18,93;,
  3;20,93,18;,
  3;129,124,57;,
  3;57,92,129;,
  3;79,81,92;,
  3;92,93,79;,
  3;77,79,93;,
  3;93,20,77;,
  3;113,77,20;,
  3;23,47,7;,
  3;94,49,47;,
  3;47,23,94;,
  3;25,94,23;,
  3;95,51,49;,
  3;49,94,95;,
  3;96,95,94;,
  3;94,25,96;,
  3;27,96,25;,
  3;130,122,51;,
  3;51,95,130;,
  3;66,68,95;,
  3;95,96,66;,
  3;64,66,96;,
  3;96,27,64;,
  3;115,64,27;,
  3;29,40,1;,
  3;97,42,40;,
  3;40,29,97;,
  3;31,97,29;,
  3;98,44,42;,
  3;42,97,98;,
  3;99,98,97;,
  3;97,31,99;,
  3;33,99,31;,
  3;131,120,44;,
  3;44,98,131;,
  3;73,75,98;,
  3;98,99,73;,
  3;71,73,99;,
  3;99,33,71;,
  3;117,71,33;,
  3;6,59,22;,
  3;59,61,100;,
  3;100,22,59;,
  3;22,100,24;,
  3;61,63,101;,
  3;101,100,61;,
  3;100,101,102;,
  3;102,24,100;,
  3;24,102,26;,
  3;63,127,132;,
  3;132,101,63;,
  3;101,80,78;,
  3;78,102,101;,
  3;102,78,76;,
  3;76,26,102;,
  3;26,76,114;,
  3;9,46,35;,
  3;46,48,103;,
  3;103,35,46;,
  3;35,103,37;,
  3;48,50,104;,
  3;104,103,48;,
  3;103,104,105;,
  3;105,37,103;,
  3;37,105,39;,
  3;50,123,133;,
  3;133,104,50;,
  3;104,74,72;,
  3;72,105,104;,
  3;105,72,70;,
  3;70,39,105;,
  3;39,70,118;,
  3;0,52,28;,
  3;52,54,106;,
  3;106,28,52;,
  3;28,106,30;,
  3;54,56,107;,
  3;107,106,54;,
  3;106,107,108;,
  3;108,30,106;,
  3;30,108,32;,
  3;56,125,134;,
  3;134,107,56;,
  3;107,87,85;,
  3;85,108,107;,
  3;108,85,83;,
  3;83,32,108;,
  3;32,83,116;,
  3;34,58,8;,
  3;109,60,58;,
  3;58,34,109;,
  3;36,109,34;,
  3;110,62,60;,
  3;60,109,110;,
  3;111,110,109;,
  3;109,36,111;,
  3;38,111,36;,
  3;135,126,62;,
  3;62,110,135;,
  3;84,86,110;,
  3;110,111,84;,
  3;82,84,111;,
  3;111,38,82;,
  3;119,82,38;;
 }
 MeshTextureCoords {
  138;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
