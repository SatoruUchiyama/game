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
 -19.26446;80.83015;2.33028;,
 21.97951;74.64719;-19.64923;,
 0.00000;62.57316;-28.75341;,
 -19.26446;80.83015;2.33028;,
 31.08369;74.64719;2.33028;,
 -19.26446;80.83015;2.33028;,
 21.97951;74.64719;24.30979;,
 -19.26446;80.83015;2.33028;,
 -6.51934;60.61001;26.20715;,
 -19.26446;80.83015;2.33028;,
 -21.97951;74.64719;24.30979;,
 -19.26446;80.83015;2.33028;,
 -50.34823;74.64719;2.33028;,
 -19.26446;80.83015;2.33028;,
 -21.97951;74.64719;-19.64923;,
 -19.26446;80.83015;2.33028;,
 0.00000;62.57316;-28.75341;,
 22.52413;57.03973;-22.71705;,
 0.00000;57.03973;-55.10497;,
 57.43525;57.03973;2.33028;,
 40.61285;57.03973;42.94313;,
 -21.88318;50.79609;62.18736;,
 -40.61285;57.03973;42.94313;,
 -67.46372;65.12933;14.69453;,
 -40.61285;57.03973;-38.28258;,
 0.00000;57.03973;-55.10497;,
 53.06319;30.68817;-50.73292;,
 23.78028;28.44878;-62.24609;,
 48.95538;30.68817;2.33028;,
 53.06319;30.68817;55.39349;,
 0.00000;30.68817;77.37299;,
 -53.06328;30.68817;55.39349;,
 -75.04274;16.82871;2.33028;,
 -40.24180;30.68817;-50.73292;,
 23.78028;28.44878;-62.24609;,
 57.43525;-0.39552;-55.10497;,
 0.00000;-0.39552;-78.89542;,
 81.22571;-0.39552;2.33028;,
 57.43525;-0.39552;59.76555;,
 0.00000;-0.39552;58.65753;,
 -57.43525;-0.39552;59.76555;,
 -81.22571;-0.39552;2.33028;,
 -57.43525;-0.39552;-55.10497;,
 0.00000;-0.39552;-78.89542;,
 0.00000;-0.39552;58.65753;,
 81.22571;-0.39552;2.33028;,
 57.43525;-0.39552;59.76555;,
 0.00000;-0.39552;-78.89542;,
 57.43525;-0.39552;-55.10497;,
 -81.22571;-0.39552;2.33028;,
 -57.43525;-0.39552;-55.10497;,
 -57.43525;-0.39552;59.76555;;
 
 38;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;18,17,26,27;,
 4;17,19,28,26;,
 4;19,20,29,28;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;27,26,35,36;,
 4;26,28,37,35;,
 4;28,29,38,37;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 3;44,45,46;,
 3;45,47,48;,
 3;47,49,50;,
 3;49,44,51;,
 3;44,47,45;,
 3;47,44,49;;
 
 MeshMaterialList {
  3;
  38;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/object/rock_00.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/object/rock_01.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/object/rock_02.jpg";
   }
  }
 }
 MeshNormals {
  42;
  0.104367;0.990119;-0.093662;,
  0.132868;0.836363;-0.531830;,
  0.284957;0.804409;-0.521273;,
  0.269747;0.959842;0.077074;,
  0.069810;0.904115;0.421548;,
  -0.069964;0.773937;0.629385;,
  0.102632;0.901703;0.419999;,
  -0.311915;0.950109;-0.001641;,
  -0.089644;0.916316;-0.390293;,
  0.131747;0.688736;-0.712941;,
  0.595845;0.560778;-0.574888;,
  0.868625;0.462079;-0.178815;,
  0.231383;0.804528;0.546988;,
  -0.035195;0.701145;0.712150;,
  -0.354874;0.664602;0.657548;,
  -0.741625;0.670560;0.018487;,
  -0.458358;0.593740;-0.661348;,
  0.071533;0.453956;-0.888148;,
  0.664502;0.483692;-0.569631;,
  0.927372;0.364622;-0.083858;,
  0.944774;0.279146;0.171697;,
  -0.057564;0.185335;0.980988;,
  -0.636236;0.222467;0.738723;,
  -0.915497;0.354667;0.189936;,
  -0.594346;0.365263;-0.716475;,
  0.060102;0.344599;-0.936824;,
  0.690057;0.383660;-0.613700;,
  0.871774;0.489908;-0.000000;,
  0.858622;0.482516;0.173050;,
  0.000000;-0.190828;0.981623;,
  -0.169670;-0.188062;0.967391;,
  -0.936529;0.350317;-0.013832;,
  -0.584643;0.463433;-0.665900;,
  -0.276182;0.655697;0.702699;,
  0.625760;0.727298;0.281891;,
  0.737103;0.408008;-0.538710;,
  0.984836;0.062159;0.161969;,
  0.224661;0.234578;0.945780;,
  -0.844127;0.237087;-0.480874;,
  0.169670;-0.188062;0.967391;,
  -0.903300;0.246780;0.350925;,
  0.000000;-1.000000;-0.000000;;
  38;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;33,5,4;,
  3;0,6,34;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,35,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,36,20,19;,
  4;12,13,21,37;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,38;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;37,21,29,39;,
  4;21,22,30,29;,
  4;22,23,31,40;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;;
 }
 MeshTextureCoords {
  52;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
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
