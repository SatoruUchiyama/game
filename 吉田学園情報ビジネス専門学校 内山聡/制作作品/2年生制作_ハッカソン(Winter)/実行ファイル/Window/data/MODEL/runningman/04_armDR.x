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
 52;
 -10.91620;0.00000;3.42720;,
 -10.91620;-2.42340;2.42340;,
 -7.84060;-2.81450;2.81450;,
 -7.84060;0.00000;3.98030;,
 -10.91620;-3.42720;0.00000;,
 -7.84060;-3.98030;0.00000;,
 -10.91620;-2.42340;-2.42340;,
 -7.84060;-2.81450;-2.81450;,
 -10.91620;0.00000;-3.42720;,
 -7.84060;0.00000;-3.98030;,
 -10.91620;2.42340;-2.42340;,
 -7.84060;2.81450;-2.81450;,
 -10.91620;3.42720;0.00000;,
 -7.84060;3.98030;0.00000;,
 -10.91620;2.42340;2.42340;,
 -7.84060;2.81450;2.81450;,
 -10.91620;0.00000;3.42720;,
 -7.84060;0.00000;3.98030;,
 -3.95490;-2.81450;2.81450;,
 -3.95490;0.00000;3.98030;,
 -3.95490;-3.98030;-0.00000;,
 -3.95490;-2.81450;-2.81450;,
 -3.95490;0.00000;-3.98030;,
 -3.95490;2.81450;-2.81450;,
 -3.95490;3.98030;-0.00000;,
 -3.95490;2.81450;2.81450;,
 -3.95490;0.00000;3.98030;,
 -0.87930;-2.42340;2.42340;,
 -0.87930;0.00000;3.42720;,
 -0.87930;-3.42720;-0.00000;,
 -0.87930;-2.42340;-2.42340;,
 -0.87930;0.00000;-3.42720;,
 -0.87930;2.42340;-2.42340;,
 -0.87930;3.42720;-0.00000;,
 -0.87930;2.42340;2.42340;,
 -0.87930;0.00000;3.42720;,
 -11.71820;0.00000;0.00000;,
 -11.71820;0.00000;0.00000;,
 -11.71820;0.00000;0.00000;,
 -11.71820;0.00000;0.00000;,
 -11.71820;0.00000;0.00000;,
 -11.71820;0.00000;0.00000;,
 -11.71820;0.00000;0.00000;,
 -11.71820;0.00000;0.00000;,
 -0.32140;0.00000;-0.00000;,
 -0.32140;0.00000;-0.00000;,
 -0.32140;0.00000;-0.00000;,
 -0.32140;0.00000;-0.00000;,
 -0.32140;0.00000;-0.00000;,
 -0.32140;0.00000;-0.00000;,
 -0.32140;0.00000;-0.00000;,
 -0.32140;0.00000;-0.00000;;
 
 40;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;3,2,18,19;,
 4;2,5,20,18;,
 4;5,7,21,20;,
 4;7,9,22,21;,
 4;9,11,23,22;,
 4;11,13,24,23;,
 4;13,15,25,24;,
 4;15,17,26,25;,
 4;19,18,27,28;,
 4;18,20,29,27;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;25,26,35,34;,
 3;36,1,0;,
 3;37,4,1;,
 3;38,6,4;,
 3;39,8,6;,
 3;40,10,8;,
 3;41,12,10;,
 3;42,14,12;,
 3;43,16,14;,
 3;44,28,27;,
 3;45,27,29;,
 3;46,29,30;,
 3;47,30,31;,
 3;48,31,32;,
 3;49,32,33;,
 3;50,33,34;,
 3;51,34,35;;
 
 MeshMaterialList {
  1;
  40;
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
   0.949000;0.773000;0.522000;1.000000;;
   1.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  50;
  -1.000000;-0.000000;0.000000;,
  -0.176995;0.000000;0.984212;,
  -0.176995;-0.695943;0.695943;,
  -0.176995;-0.984212;0.000000;,
  -0.176996;-0.695943;-0.695943;,
  -0.176995;0.000000;-0.984212;,
  -0.176996;0.695943;-0.695943;,
  -0.176995;0.984212;0.000000;,
  -0.176995;0.695943;0.695943;,
  -0.088951;0.000000;0.996036;,
  -0.088951;-0.704304;0.704304;,
  -0.088951;-0.996036;0.000000;,
  -0.088951;-0.704304;-0.704304;,
  -0.088951;0.000000;-0.996036;,
  -0.088951;0.704304;-0.704304;,
  -0.088951;0.996036;0.000000;,
  -0.088951;0.704304;0.704304;,
  0.088951;0.000000;0.996036;,
  0.088951;-0.704304;0.704304;,
  0.088951;-0.996036;-0.000000;,
  0.088951;-0.704304;-0.704304;,
  0.088951;0.000000;-0.996036;,
  0.088951;0.704304;-0.704304;,
  0.088951;0.996036;0.000000;,
  0.088951;0.704304;0.704304;,
  0.176995;0.000000;0.984212;,
  0.176996;-0.695943;0.695943;,
  0.176995;-0.984212;-0.000000;,
  0.176995;-0.695943;-0.695943;,
  0.176995;0.000000;-0.984212;,
  0.176995;0.695943;-0.695943;,
  0.176995;0.984212;0.000000;,
  0.176996;0.695943;0.695943;,
  1.000000;0.000000;-0.000000;,
  -0.973695;-0.161117;0.161117;,
  -0.973695;0.000000;0.227855;,
  -0.973695;-0.227855;0.000000;,
  -0.973695;-0.161117;-0.161117;,
  -0.973695;0.000000;-0.227854;,
  -0.973695;0.161117;-0.161117;,
  -0.973695;0.227855;0.000000;,
  -0.973695;0.161117;0.161117;,
  0.987008;0.000000;0.160671;,
  0.987008;-0.113611;0.113611;,
  0.987008;-0.160671;-0.000000;,
  0.987008;-0.113611;-0.113611;,
  0.987008;0.000000;-0.160671;,
  0.987008;0.113611;-0.113611;,
  0.987008;0.160671;0.000000;,
  0.987008;0.113611;0.113611;;
  40;
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  3;0,34,35;,
  3;0,36,34;,
  3;0,37,36;,
  3;0,38,37;,
  3;0,39,38;,
  3;0,40,39;,
  3;0,41,40;,
  3;0,35,41;,
  3;33,42,43;,
  3;33,43,44;,
  3;33,44,45;,
  3;33,45,46;,
  3;33,46,47;,
  3;33,47,48;,
  3;33,48,49;,
  3;33,49,42;;
 }
 MeshTextureCoords {
  52;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;0.333330;,
  0.000000;0.333330;,
  0.250000;0.000000;,
  0.250000;0.333330;,
  0.375000;0.000000;,
  0.375000;0.333330;,
  0.500000;0.000000;,
  0.500000;0.333330;,
  0.625000;0.000000;,
  0.625000;0.333330;,
  0.750000;0.000000;,
  0.750000;0.333330;,
  0.875000;0.000000;,
  0.875000;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.125000;0.666670;,
  0.000000;0.666670;,
  0.250000;0.666670;,
  0.375000;0.666670;,
  0.500000;0.666670;,
  0.625000;0.666670;,
  0.750000;0.666670;,
  0.875000;0.666670;,
  1.000000;0.666670;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
