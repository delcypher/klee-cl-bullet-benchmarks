#include <stdint.h>
#include <stdio.h>
#include <CL/cl.h>

static char opencl_code[] = "\
#pragma OPENCL EXTENSION cl_khr_fp64: enable\n\
struct CPbinding {\n\
  uchar n16;\n\
  uchar n18;\n\
  uchar n20;\n\
  uchar n21;\n\
  ushort n19;\n\
  uint n17;\n\
  uint n15;\n\
  float n14;\n\
  float n13;\n\
  float n12;\n\
  float n11;\n\
  float n10;\n\
  float n27;\n\
  float n26;\n\
  float n32;\n\
  float n35;\n\
  float n34;\n\
  float n33;\n\
  float n31;\n\
  float n38;\n\
  float n37;\n\
  float n36;\n\
  float n30;\n\
  float n29;\n\
  float n40;\n\
  float n39;\n\
  float n28;\n\
  float n25;\n\
  float n24;\n\
  float n23;\n\
  float n45;\n\
  float n48;\n\
  float n50;\n\
  float n49;\n\
  float n47;\n\
  float n46;\n\
  float n44;\n\
  float n53;\n\
  float n55;\n\
  float n54;\n\
  float n52;\n\
  float n51;\n\
  float n43;\n\
  float n42;\n\
  float n57;\n\
  float n56;\n\
  float n41;\n\
  float n22;\n\
  float n9;\n\
  float n60;\n\
  float n59;\n\
  float n65;\n\
  float n68;\n\
  float n70;\n\
  float n69;\n\
  float n67;\n\
  float n66;\n\
  float n64;\n\
  float n73;\n\
  float n75;\n\
  float n74;\n\
  float n72;\n\
  float n71;\n\
  float n63;\n\
  float n62;\n\
  float n77;\n\
  float n76;\n\
  float n61;\n\
  float n58;\n\
  float n8;\n\
  float n81;\n\
  float n84;\n\
  float n83;\n\
  float n89;\n\
  float n92;\n\
  float n94;\n\
  float n93;\n\
  float n91;\n\
  float n90;\n\
  float n88;\n\
  float n97;\n\
  float n99;\n\
  float n98;\n\
  float n96;\n\
  float n95;\n\
  float n87;\n\
  float n86;\n\
  float n101;\n\
  float n100;\n\
  float n85;\n\
  float n82;\n\
  float n80;\n\
  float n79;\n\
  float n106;\n\
  float n109;\n\
  float n111;\n\
  float n110;\n\
  float n108;\n\
  float n107;\n\
  float n105;\n\
  float n114;\n\
  float n116;\n\
  float n115;\n\
  float n113;\n\
  float n112;\n\
  float n104;\n\
  float n103;\n\
  float n118;\n\
  float n117;\n\
  float n102;\n\
  float n78;\n\
  float n7;\n\
  float n121;\n\
  float n120;\n\
  float n126;\n\
  float n129;\n\
  float n131;\n\
  float n130;\n\
  float n128;\n\
  float n127;\n\
  float n125;\n\
  float n134;\n\
  float n136;\n\
  float n135;\n\
  float n133;\n\
  float n132;\n\
  float n124;\n\
  float n123;\n\
  float n138;\n\
  float n137;\n\
  float n122;\n\
  float n119;\n\
  float n6;\n\
  float n142;\n\
  float n145;\n\
  float n144;\n\
  float n150;\n\
  float n153;\n\
  float n155;\n\
  float n154;\n\
  float n152;\n\
  float n151;\n\
  float n149;\n\
  float n158;\n\
  float n160;\n\
  float n159;\n\
  float n157;\n\
  float n156;\n\
  float n148;\n\
  float n147;\n\
  float n162;\n\
  float n161;\n\
  float n146;\n\
  float n143;\n\
  float n141;\n\
  float n140;\n\
  float n167;\n\
  float n170;\n\
  float n172;\n\
  float n171;\n\
  float n169;\n\
  float n168;\n\
  float n166;\n\
  float n175;\n\
  float n177;\n\
  float n176;\n\
  float n174;\n\
  float n173;\n\
  float n165;\n\
  float n164;\n\
  float n179;\n\
  float n178;\n\
  float n163;\n\
  float n139;\n\
  float n5;\n\
  float n182;\n\
  float n181;\n\
  float n187;\n\
  float n190;\n\
  float n192;\n\
  float n191;\n\
  float n189;\n\
  float n188;\n\
  float n186;\n\
  float n195;\n\
  float n197;\n\
  float n196;\n\
  float n194;\n\
  float n193;\n\
  float n185;\n\
  float n184;\n\
  float n199;\n\
  float n198;\n\
  float n183;\n\
  float n180;\n\
  float n4;\n\
  float n203;\n\
  float n206;\n\
  float n205;\n\
  float n211;\n\
  float n214;\n\
  float n216;\n\
  float n215;\n\
  float n213;\n\
  float n212;\n\
  float n210;\n\
  float n219;\n\
  float n221;\n\
  float n220;\n\
  float n218;\n\
  float n217;\n\
  float n209;\n\
  float n208;\n\
  float n223;\n\
  float n222;\n\
  float n207;\n\
  float n204;\n\
  float n202;\n\
  float n201;\n\
  float n228;\n\
  float n231;\n\
  float n233;\n\
  float n232;\n\
  float n230;\n\
  float n229;\n\
  float n227;\n\
  float n236;\n\
  float n238;\n\
  float n237;\n\
  float n235;\n\
  float n234;\n\
  float n226;\n\
  float n225;\n\
  float n240;\n\
  float n239;\n\
  float n224;\n\
  float n200;\n\
  float n3;\n\
  float n243;\n\
  float n242;\n\
  float n248;\n\
  float n251;\n\
  float n253;\n\
  float n252;\n\
  float n250;\n\
  float n249;\n\
  float n247;\n\
  float n256;\n\
  float n258;\n\
  float n257;\n\
  float n255;\n\
  float n254;\n\
  float n246;\n\
  float n245;\n\
  float n260;\n\
  float n259;\n\
  float n244;\n\
  float n241;\n\
  float n2;\n\
  float n264;\n\
  float n267;\n\
  float n266;\n\
  float n272;\n\
  float n275;\n\
  float n277;\n\
  float n276;\n\
  float n274;\n\
  float n273;\n\
  float n271;\n\
  float n280;\n\
  float n282;\n\
  float n281;\n\
  float n279;\n\
  float n278;\n\
  float n270;\n\
  float n269;\n\
  float n284;\n\
  float n283;\n\
  float n268;\n\
  float n265;\n\
  float n263;\n\
  float n262;\n\
  float n289;\n\
  float n292;\n\
  float n294;\n\
  float n293;\n\
  float n291;\n\
  float n290;\n\
  float n288;\n\
  float n297;\n\
  float n299;\n\
  float n298;\n\
  float n296;\n\
  float n295;\n\
  float n287;\n\
  float n286;\n\
  float n301;\n\
  float n300;\n\
  float n285;\n\
  float n261;\n\
  float n1;\n\
  double n0;\n\
};\n\
\n\
typedef int CPbinding_size_matches[sizeof(struct CPbinding) == HOST_SIZEOF_CPBINDING ? 1 : -1];\n\
\n\
__kernel void CPeval(__global struct CPbinding *bindings, __global char *kLST) {\n\
  bindings->n16 = kLST[((uint)3UL)];\n\
  bindings->n18 = kLST[((uint)2UL)];\n\
  bindings->n20 = kLST[((uint)1UL)];\n\
  bindings->n21 = kLST[((uint)0UL)];\n\
  bindings->n19 = (((ushort) bindings->n20) << 8) | (((ushort) bindings->n21) & 255UL);\n\
  bindings->n17 = (((uint) bindings->n18) << 16) | (((uint) bindings->n19) & 65535UL);\n\
  bindings->n15 = (((uint) bindings->n16) << 24) | (bindings->n17 & 16777215UL);\n\
  bindings->n14 = 2.f / (*(float *) &bindings->n15);\n\
  bindings->n13 = bindings->n14 * 54.f;\n\
  bindings->n12 = -1.9073486328125e-06f / bindings->n13;\n\
  bindings->n11 = 3.f * bindings->n12;\n\
  bindings->n10 = 1.f - bindings->n11;\n\
  bindings->n27 = 4.f + bindings->n11;\n\
  bindings->n26 = 7.f - bindings->n27;\n\
  bindings->n32 = bindings->n26 * bindings->n26;\n\
  bindings->n35 = 5.f + bindings->n11;\n\
  bindings->n34 = 8.f - bindings->n35;\n\
  bindings->n33 = bindings->n34 * bindings->n34;\n\
  bindings->n31 = bindings->n32 + bindings->n33;\n\
  bindings->n38 = 6.f + bindings->n11;\n\
  bindings->n37 = 9.f - bindings->n38;\n\
  bindings->n36 = bindings->n37 * bindings->n37;\n\
  bindings->n30 = bindings->n31 + bindings->n36;\n\
  bindings->n29 = 26.999998092651367188f - bindings->n30;\n\
  bindings->n40 = 26.999998092651367188f + bindings->n30;\n\
  bindings->n39 = bindings->n14 * bindings->n40;\n\
  bindings->n28 = bindings->n29 / bindings->n39;\n\
  bindings->n25 = bindings->n26 * bindings->n28;\n\
  bindings->n24 = 7.f + bindings->n25;\n\
  bindings->n23 = bindings->n10 - bindings->n24;\n\
  bindings->n45 = bindings->n23 * bindings->n23;\n\
  bindings->n48 = 2.f - bindings->n11;\n\
  bindings->n50 = bindings->n34 * bindings->n28;\n\
  bindings->n49 = 8.f + bindings->n50;\n\
  bindings->n47 = bindings->n48 - bindings->n49;\n\
  bindings->n46 = bindings->n47 * bindings->n47;\n\
  bindings->n44 = bindings->n45 + bindings->n46;\n\
  bindings->n53 = 3.f - bindings->n11;\n\
  bindings->n55 = bindings->n37 * bindings->n28;\n\
  bindings->n54 = 9.f + bindings->n55;\n\
  bindings->n52 = bindings->n53 - bindings->n54;\n\
  bindings->n51 = bindings->n52 * bindings->n52;\n\
  bindings->n43 = bindings->n44 + bindings->n51;\n\
  bindings->n42 = 107.99999237060546875f - bindings->n43;\n\
  bindings->n57 = 107.99999237060546875f + bindings->n43;\n\
  bindings->n56 = bindings->n14 * bindings->n57;\n\
  bindings->n41 = bindings->n42 / bindings->n56;\n\
  bindings->n22 = bindings->n23 * bindings->n41;\n\
  bindings->n9 = bindings->n10 + bindings->n22;\n\
  bindings->n60 = bindings->n27 - bindings->n25;\n\
  bindings->n59 = bindings->n60 - bindings->n9;\n\
  bindings->n65 = bindings->n59 * bindings->n59;\n\
  bindings->n68 = bindings->n35 - bindings->n50;\n\
  bindings->n70 = bindings->n47 * bindings->n41;\n\
  bindings->n69 = bindings->n48 + bindings->n70;\n\
  bindings->n67 = bindings->n68 - bindings->n69;\n\
  bindings->n66 = bindings->n67 * bindings->n67;\n\
  bindings->n64 = bindings->n65 + bindings->n66;\n\
  bindings->n73 = bindings->n38 - bindings->n55;\n\
  bindings->n75 = bindings->n52 * bindings->n41;\n\
  bindings->n74 = bindings->n53 + bindings->n75;\n\
  bindings->n72 = bindings->n73 - bindings->n74;\n\
  bindings->n71 = bindings->n72 * bindings->n72;\n\
  bindings->n63 = bindings->n64 + bindings->n71;\n\
  bindings->n62 = 26.999998092651367188f - bindings->n63;\n\
  bindings->n77 = 26.999998092651367188f + bindings->n63;\n\
  bindings->n76 = bindings->n14 * bindings->n77;\n\
  bindings->n61 = bindings->n62 / bindings->n76;\n\
  bindings->n58 = bindings->n59 * bindings->n61;\n\
  bindings->n8 = bindings->n9 - bindings->n58;\n\
  bindings->n81 = bindings->n24 - bindings->n22;\n\
  bindings->n84 = bindings->n60 + bindings->n58;\n\
  bindings->n83 = bindings->n81 - bindings->n84;\n\
  bindings->n89 = bindings->n83 * bindings->n83;\n\
  bindings->n92 = bindings->n49 - bindings->n70;\n\
  bindings->n94 = bindings->n67 * bindings->n61;\n\
  bindings->n93 = bindings->n68 + bindings->n94;\n\
  bindings->n91 = bindings->n92 - bindings->n93;\n\
  bindings->n90 = bindings->n91 * bindings->n91;\n\
  bindings->n88 = bindings->n89 + bindings->n90;\n\
  bindings->n97 = bindings->n54 - bindings->n75;\n\
  bindings->n99 = bindings->n72 * bindings->n61;\n\
  bindings->n98 = bindings->n73 + bindings->n99;\n\
  bindings->n96 = bindings->n97 - bindings->n98;\n\
  bindings->n95 = bindings->n96 * bindings->n96;\n\
  bindings->n87 = bindings->n88 + bindings->n95;\n\
  bindings->n86 = 26.999998092651367188f - bindings->n87;\n\
  bindings->n101 = 26.999998092651367188f + bindings->n87;\n\
  bindings->n100 = bindings->n14 * bindings->n101;\n\
  bindings->n85 = bindings->n86 / bindings->n100;\n\
  bindings->n82 = bindings->n83 * bindings->n85;\n\
  bindings->n80 = bindings->n81 + bindings->n82;\n\
  bindings->n79 = bindings->n8 - bindings->n80;\n\
  bindings->n106 = bindings->n79 * bindings->n79;\n\
  bindings->n109 = bindings->n69 - bindings->n94;\n\
  bindings->n111 = bindings->n91 * bindings->n85;\n\
  bindings->n110 = bindings->n92 + bindings->n111;\n\
  bindings->n108 = bindings->n109 - bindings->n110;\n\
  bindings->n107 = bindings->n108 * bindings->n108;\n\
  bindings->n105 = bindings->n106 + bindings->n107;\n\
  bindings->n114 = bindings->n74 - bindings->n99;\n\
  bindings->n116 = bindings->n96 * bindings->n85;\n\
  bindings->n115 = bindings->n97 + bindings->n116;\n\
  bindings->n113 = bindings->n114 - bindings->n115;\n\
  bindings->n112 = bindings->n113 * bindings->n113;\n\
  bindings->n104 = bindings->n105 + bindings->n112;\n\
  bindings->n103 = 107.99999237060546875f - bindings->n104;\n\
  bindings->n118 = 107.99999237060546875f + bindings->n104;\n\
  bindings->n117 = bindings->n14 * bindings->n118;\n\
  bindings->n102 = bindings->n103 / bindings->n117;\n\
  bindings->n78 = bindings->n79 * bindings->n102;\n\
  bindings->n7 = bindings->n8 + bindings->n78;\n\
  bindings->n121 = bindings->n84 - bindings->n82;\n\
  bindings->n120 = bindings->n121 - bindings->n7;\n\
  bindings->n126 = bindings->n120 * bindings->n120;\n\
  bindings->n129 = bindings->n93 - bindings->n111;\n\
  bindings->n131 = bindings->n108 * bindings->n102;\n\
  bindings->n130 = bindings->n109 + bindings->n131;\n\
  bindings->n128 = bindings->n129 - bindings->n130;\n\
  bindings->n127 = bindings->n128 * bindings->n128;\n\
  bindings->n125 = bindings->n126 + bindings->n127;\n\
  bindings->n134 = bindings->n98 - bindings->n116;\n\
  bindings->n136 = bindings->n113 * bindings->n102;\n\
  bindings->n135 = bindings->n114 + bindings->n136;\n\
  bindings->n133 = bindings->n134 - bindings->n135;\n\
  bindings->n132 = bindings->n133 * bindings->n133;\n\
  bindings->n124 = bindings->n125 + bindings->n132;\n\
  bindings->n123 = 26.999998092651367188f - bindings->n124;\n\
  bindings->n138 = 26.999998092651367188f + bindings->n124;\n\
  bindings->n137 = bindings->n14 * bindings->n138;\n\
  bindings->n122 = bindings->n123 / bindings->n137;\n\
  bindings->n119 = bindings->n120 * bindings->n122;\n\
  bindings->n6 = bindings->n7 - bindings->n119;\n\
  bindings->n142 = bindings->n80 - bindings->n78;\n\
  bindings->n145 = bindings->n121 + bindings->n119;\n\
  bindings->n144 = bindings->n142 - bindings->n145;\n\
  bindings->n150 = bindings->n144 * bindings->n144;\n\
  bindings->n153 = bindings->n110 - bindings->n131;\n\
  bindings->n155 = bindings->n128 * bindings->n122;\n\
  bindings->n154 = bindings->n129 + bindings->n155;\n\
  bindings->n152 = bindings->n153 - bindings->n154;\n\
  bindings->n151 = bindings->n152 * bindings->n152;\n\
  bindings->n149 = bindings->n150 + bindings->n151;\n\
  bindings->n158 = bindings->n115 - bindings->n136;\n\
  bindings->n160 = bindings->n133 * bindings->n122;\n\
  bindings->n159 = bindings->n134 + bindings->n160;\n\
  bindings->n157 = bindings->n158 - bindings->n159;\n\
  bindings->n156 = bindings->n157 * bindings->n157;\n\
  bindings->n148 = bindings->n149 + bindings->n156;\n\
  bindings->n147 = 26.999998092651367188f - bindings->n148;\n\
  bindings->n162 = 26.999998092651367188f + bindings->n148;\n\
  bindings->n161 = bindings->n14 * bindings->n162;\n\
  bindings->n146 = bindings->n147 / bindings->n161;\n\
  bindings->n143 = bindings->n144 * bindings->n146;\n\
  bindings->n141 = bindings->n142 + bindings->n143;\n\
  bindings->n140 = bindings->n6 - bindings->n141;\n\
  bindings->n167 = bindings->n140 * bindings->n140;\n\
  bindings->n170 = bindings->n130 - bindings->n155;\n\
  bindings->n172 = bindings->n152 * bindings->n146;\n\
  bindings->n171 = bindings->n153 + bindings->n172;\n\
  bindings->n169 = bindings->n170 - bindings->n171;\n\
  bindings->n168 = bindings->n169 * bindings->n169;\n\
  bindings->n166 = bindings->n167 + bindings->n168;\n\
  bindings->n175 = bindings->n135 - bindings->n160;\n\
  bindings->n177 = bindings->n157 * bindings->n146;\n\
  bindings->n176 = bindings->n158 + bindings->n177;\n\
  bindings->n174 = bindings->n175 - bindings->n176;\n\
  bindings->n173 = bindings->n174 * bindings->n174;\n\
  bindings->n165 = bindings->n166 + bindings->n173;\n\
  bindings->n164 = 107.99999237060546875f - bindings->n165;\n\
  bindings->n179 = 107.99999237060546875f + bindings->n165;\n\
  bindings->n178 = bindings->n14 * bindings->n179;\n\
  bindings->n163 = bindings->n164 / bindings->n178;\n\
  bindings->n139 = bindings->n140 * bindings->n163;\n\
  bindings->n5 = bindings->n6 + bindings->n139;\n\
  bindings->n182 = bindings->n145 - bindings->n143;\n\
  bindings->n181 = bindings->n182 - bindings->n5;\n\
  bindings->n187 = bindings->n181 * bindings->n181;\n\
  bindings->n190 = bindings->n154 - bindings->n172;\n\
  bindings->n192 = bindings->n169 * bindings->n163;\n\
  bindings->n191 = bindings->n170 + bindings->n192;\n\
  bindings->n189 = bindings->n190 - bindings->n191;\n\
  bindings->n188 = bindings->n189 * bindings->n189;\n\
  bindings->n186 = bindings->n187 + bindings->n188;\n\
  bindings->n195 = bindings->n159 - bindings->n177;\n\
  bindings->n197 = bindings->n174 * bindings->n163;\n\
  bindings->n196 = bindings->n175 + bindings->n197;\n\
  bindings->n194 = bindings->n195 - bindings->n196;\n\
  bindings->n193 = bindings->n194 * bindings->n194;\n\
  bindings->n185 = bindings->n186 + bindings->n193;\n\
  bindings->n184 = 26.999998092651367188f - bindings->n185;\n\
  bindings->n199 = 26.999998092651367188f + bindings->n185;\n\
  bindings->n198 = bindings->n14 * bindings->n199;\n\
  bindings->n183 = bindings->n184 / bindings->n198;\n\
  bindings->n180 = bindings->n181 * bindings->n183;\n\
  bindings->n4 = bindings->n5 - bindings->n180;\n\
  bindings->n203 = bindings->n141 - bindings->n139;\n\
  bindings->n206 = bindings->n182 + bindings->n180;\n\
  bindings->n205 = bindings->n203 - bindings->n206;\n\
  bindings->n211 = bindings->n205 * bindings->n205;\n\
  bindings->n214 = bindings->n171 - bindings->n192;\n\
  bindings->n216 = bindings->n189 * bindings->n183;\n\
  bindings->n215 = bindings->n190 + bindings->n216;\n\
  bindings->n213 = bindings->n214 - bindings->n215;\n\
  bindings->n212 = bindings->n213 * bindings->n213;\n\
  bindings->n210 = bindings->n211 + bindings->n212;\n\
  bindings->n219 = bindings->n176 - bindings->n197;\n\
  bindings->n221 = bindings->n194 * bindings->n183;\n\
  bindings->n220 = bindings->n195 + bindings->n221;\n\
  bindings->n218 = bindings->n219 - bindings->n220;\n\
  bindings->n217 = bindings->n218 * bindings->n218;\n\
  bindings->n209 = bindings->n210 + bindings->n217;\n\
  bindings->n208 = 26.999998092651367188f - bindings->n209;\n\
  bindings->n223 = 26.999998092651367188f + bindings->n209;\n\
  bindings->n222 = bindings->n14 * bindings->n223;\n\
  bindings->n207 = bindings->n208 / bindings->n222;\n\
  bindings->n204 = bindings->n205 * bindings->n207;\n\
  bindings->n202 = bindings->n203 + bindings->n204;\n\
  bindings->n201 = bindings->n4 - bindings->n202;\n\
  bindings->n228 = bindings->n201 * bindings->n201;\n\
  bindings->n231 = bindings->n191 - bindings->n216;\n\
  bindings->n233 = bindings->n213 * bindings->n207;\n\
  bindings->n232 = bindings->n214 + bindings->n233;\n\
  bindings->n230 = bindings->n231 - bindings->n232;\n\
  bindings->n229 = bindings->n230 * bindings->n230;\n\
  bindings->n227 = bindings->n228 + bindings->n229;\n\
  bindings->n236 = bindings->n196 - bindings->n221;\n\
  bindings->n238 = bindings->n218 * bindings->n207;\n\
  bindings->n237 = bindings->n219 + bindings->n238;\n\
  bindings->n235 = bindings->n236 - bindings->n237;\n\
  bindings->n234 = bindings->n235 * bindings->n235;\n\
  bindings->n226 = bindings->n227 + bindings->n234;\n\
  bindings->n225 = 107.99999237060546875f - bindings->n226;\n\
  bindings->n240 = 107.99999237060546875f + bindings->n226;\n\
  bindings->n239 = bindings->n14 * bindings->n240;\n\
  bindings->n224 = bindings->n225 / bindings->n239;\n\
  bindings->n200 = bindings->n201 * bindings->n224;\n\
  bindings->n3 = bindings->n4 + bindings->n200;\n\
  bindings->n243 = bindings->n206 - bindings->n204;\n\
  bindings->n242 = bindings->n243 - bindings->n3;\n\
  bindings->n248 = bindings->n242 * bindings->n242;\n\
  bindings->n251 = bindings->n215 - bindings->n233;\n\
  bindings->n253 = bindings->n230 * bindings->n224;\n\
  bindings->n252 = bindings->n231 + bindings->n253;\n\
  bindings->n250 = bindings->n251 - bindings->n252;\n\
  bindings->n249 = bindings->n250 * bindings->n250;\n\
  bindings->n247 = bindings->n248 + bindings->n249;\n\
  bindings->n256 = bindings->n220 - bindings->n238;\n\
  bindings->n258 = bindings->n235 * bindings->n224;\n\
  bindings->n257 = bindings->n236 + bindings->n258;\n\
  bindings->n255 = bindings->n256 - bindings->n257;\n\
  bindings->n254 = bindings->n255 * bindings->n255;\n\
  bindings->n246 = bindings->n247 + bindings->n254;\n\
  bindings->n245 = 26.999998092651367188f - bindings->n246;\n\
  bindings->n260 = 26.999998092651367188f + bindings->n246;\n\
  bindings->n259 = bindings->n14 * bindings->n260;\n\
  bindings->n244 = bindings->n245 / bindings->n259;\n\
  bindings->n241 = bindings->n242 * bindings->n244;\n\
  bindings->n2 = bindings->n3 - bindings->n241;\n\
  bindings->n264 = bindings->n202 - bindings->n200;\n\
  bindings->n267 = bindings->n243 + bindings->n241;\n\
  bindings->n266 = bindings->n264 - bindings->n267;\n\
  bindings->n272 = bindings->n266 * bindings->n266;\n\
  bindings->n275 = bindings->n232 - bindings->n253;\n\
  bindings->n277 = bindings->n250 * bindings->n244;\n\
  bindings->n276 = bindings->n251 + bindings->n277;\n\
  bindings->n274 = bindings->n275 - bindings->n276;\n\
  bindings->n273 = bindings->n274 * bindings->n274;\n\
  bindings->n271 = bindings->n272 + bindings->n273;\n\
  bindings->n280 = bindings->n237 - bindings->n258;\n\
  bindings->n282 = bindings->n255 * bindings->n244;\n\
  bindings->n281 = bindings->n256 + bindings->n282;\n\
  bindings->n279 = bindings->n280 - bindings->n281;\n\
  bindings->n278 = bindings->n279 * bindings->n279;\n\
  bindings->n270 = bindings->n271 + bindings->n278;\n\
  bindings->n269 = 26.999998092651367188f - bindings->n270;\n\
  bindings->n284 = 26.999998092651367188f + bindings->n270;\n\
  bindings->n283 = bindings->n14 * bindings->n284;\n\
  bindings->n268 = bindings->n269 / bindings->n283;\n\
  bindings->n265 = bindings->n266 * bindings->n268;\n\
  bindings->n263 = bindings->n264 + bindings->n265;\n\
  bindings->n262 = bindings->n2 - bindings->n263;\n\
  bindings->n289 = bindings->n262 * bindings->n262;\n\
  bindings->n292 = bindings->n252 - bindings->n277;\n\
  bindings->n294 = bindings->n274 * bindings->n268;\n\
  bindings->n293 = bindings->n275 + bindings->n294;\n\
  bindings->n291 = bindings->n292 - bindings->n293;\n\
  bindings->n290 = bindings->n291 * bindings->n291;\n\
  bindings->n288 = bindings->n289 + bindings->n290;\n\
  bindings->n297 = bindings->n257 - bindings->n282;\n\
  bindings->n299 = bindings->n279 * bindings->n268;\n\
  bindings->n298 = bindings->n280 + bindings->n299;\n\
  bindings->n296 = bindings->n297 - bindings->n298;\n\
  bindings->n295 = bindings->n296 * bindings->n296;\n\
  bindings->n287 = bindings->n288 + bindings->n295;\n\
  bindings->n286 = 107.99999237060546875f - bindings->n287;\n\
  bindings->n301 = 107.99999237060546875f + bindings->n287;\n\
  bindings->n300 = bindings->n14 * bindings->n301;\n\
  bindings->n285 = bindings->n286 / bindings->n300;\n\
  bindings->n261 = bindings->n262 * bindings->n285;\n\
  bindings->n1 = bindings->n2 + bindings->n261;\n\
  bindings->n0 = ((double) bindings->n1);\n\
  return;\n\
}\n\
";

struct CPbinding {
  uint8_t n16;
  uint8_t n18;
  uint8_t n20;
  uint8_t n21;
  uint16_t n19;
  uint32_t n17;
  uint32_t n15;
  float n14;
  float n13;
  float n12;
  float n11;
  float n10;
  float n27;
  float n26;
  float n32;
  float n35;
  float n34;
  float n33;
  float n31;
  float n38;
  float n37;
  float n36;
  float n30;
  float n29;
  float n40;
  float n39;
  float n28;
  float n25;
  float n24;
  float n23;
  float n45;
  float n48;
  float n50;
  float n49;
  float n47;
  float n46;
  float n44;
  float n53;
  float n55;
  float n54;
  float n52;
  float n51;
  float n43;
  float n42;
  float n57;
  float n56;
  float n41;
  float n22;
  float n9;
  float n60;
  float n59;
  float n65;
  float n68;
  float n70;
  float n69;
  float n67;
  float n66;
  float n64;
  float n73;
  float n75;
  float n74;
  float n72;
  float n71;
  float n63;
  float n62;
  float n77;
  float n76;
  float n61;
  float n58;
  float n8;
  float n81;
  float n84;
  float n83;
  float n89;
  float n92;
  float n94;
  float n93;
  float n91;
  float n90;
  float n88;
  float n97;
  float n99;
  float n98;
  float n96;
  float n95;
  float n87;
  float n86;
  float n101;
  float n100;
  float n85;
  float n82;
  float n80;
  float n79;
  float n106;
  float n109;
  float n111;
  float n110;
  float n108;
  float n107;
  float n105;
  float n114;
  float n116;
  float n115;
  float n113;
  float n112;
  float n104;
  float n103;
  float n118;
  float n117;
  float n102;
  float n78;
  float n7;
  float n121;
  float n120;
  float n126;
  float n129;
  float n131;
  float n130;
  float n128;
  float n127;
  float n125;
  float n134;
  float n136;
  float n135;
  float n133;
  float n132;
  float n124;
  float n123;
  float n138;
  float n137;
  float n122;
  float n119;
  float n6;
  float n142;
  float n145;
  float n144;
  float n150;
  float n153;
  float n155;
  float n154;
  float n152;
  float n151;
  float n149;
  float n158;
  float n160;
  float n159;
  float n157;
  float n156;
  float n148;
  float n147;
  float n162;
  float n161;
  float n146;
  float n143;
  float n141;
  float n140;
  float n167;
  float n170;
  float n172;
  float n171;
  float n169;
  float n168;
  float n166;
  float n175;
  float n177;
  float n176;
  float n174;
  float n173;
  float n165;
  float n164;
  float n179;
  float n178;
  float n163;
  float n139;
  float n5;
  float n182;
  float n181;
  float n187;
  float n190;
  float n192;
  float n191;
  float n189;
  float n188;
  float n186;
  float n195;
  float n197;
  float n196;
  float n194;
  float n193;
  float n185;
  float n184;
  float n199;
  float n198;
  float n183;
  float n180;
  float n4;
  float n203;
  float n206;
  float n205;
  float n211;
  float n214;
  float n216;
  float n215;
  float n213;
  float n212;
  float n210;
  float n219;
  float n221;
  float n220;
  float n218;
  float n217;
  float n209;
  float n208;
  float n223;
  float n222;
  float n207;
  float n204;
  float n202;
  float n201;
  float n228;
  float n231;
  float n233;
  float n232;
  float n230;
  float n229;
  float n227;
  float n236;
  float n238;
  float n237;
  float n235;
  float n234;
  float n226;
  float n225;
  float n240;
  float n239;
  float n224;
  float n200;
  float n3;
  float n243;
  float n242;
  float n248;
  float n251;
  float n253;
  float n252;
  float n250;
  float n249;
  float n247;
  float n256;
  float n258;
  float n257;
  float n255;
  float n254;
  float n246;
  float n245;
  float n260;
  float n259;
  float n244;
  float n241;
  float n2;
  float n264;
  float n267;
  float n266;
  float n272;
  float n275;
  float n277;
  float n276;
  float n274;
  float n273;
  float n271;
  float n280;
  float n282;
  float n281;
  float n279;
  float n278;
  float n270;
  float n269;
  float n284;
  float n283;
  float n268;
  float n265;
  float n263;
  float n262;
  float n289;
  float n292;
  float n294;
  float n293;
  float n291;
  float n290;
  float n288;
  float n297;
  float n299;
  float n298;
  float n296;
  float n295;
  float n287;
  float n286;
  float n301;
  float n300;
  float n285;
  float n261;
  float n1;
  double n0;
};

double CPeval(struct CPbinding *bindings, char *kLST) {
  bindings->n16 = kLST[((uint32_t)3UL)];
  bindings->n18 = kLST[((uint32_t)2UL)];
  bindings->n20 = kLST[((uint32_t)1UL)];
  bindings->n21 = kLST[((uint32_t)0UL)];
  bindings->n19 = (((uint16_t) bindings->n20) << 8) | (((uint16_t) bindings->n21) & 255ULL);
  bindings->n17 = (((uint32_t) bindings->n18) << 16) | (((uint32_t) bindings->n19) & 65535ULL);
  bindings->n15 = (((uint32_t) bindings->n16) << 24) | (bindings->n17 & 16777215ULL);
  bindings->n14 = 2.f / (*(float *) &bindings->n15);
  bindings->n13 = bindings->n14 * 54.f;
  bindings->n12 = -1.9073486328125e-06f / bindings->n13;
  bindings->n11 = 3.f * bindings->n12;
  bindings->n10 = 1.f - bindings->n11;
  bindings->n27 = 4.f + bindings->n11;
  bindings->n26 = 7.f - bindings->n27;
  bindings->n32 = bindings->n26 * bindings->n26;
  bindings->n35 = 5.f + bindings->n11;
  bindings->n34 = 8.f - bindings->n35;
  bindings->n33 = bindings->n34 * bindings->n34;
  bindings->n31 = bindings->n32 + bindings->n33;
  bindings->n38 = 6.f + bindings->n11;
  bindings->n37 = 9.f - bindings->n38;
  bindings->n36 = bindings->n37 * bindings->n37;
  bindings->n30 = bindings->n31 + bindings->n36;
  bindings->n29 = 26.999998092651367188f - bindings->n30;
  bindings->n40 = 26.999998092651367188f + bindings->n30;
  bindings->n39 = bindings->n14 * bindings->n40;
  bindings->n28 = bindings->n29 / bindings->n39;
  bindings->n25 = bindings->n26 * bindings->n28;
  bindings->n24 = 7.f + bindings->n25;
  bindings->n23 = bindings->n10 - bindings->n24;
  bindings->n45 = bindings->n23 * bindings->n23;
  bindings->n48 = 2.f - bindings->n11;
  bindings->n50 = bindings->n34 * bindings->n28;
  bindings->n49 = 8.f + bindings->n50;
  bindings->n47 = bindings->n48 - bindings->n49;
  bindings->n46 = bindings->n47 * bindings->n47;
  bindings->n44 = bindings->n45 + bindings->n46;
  bindings->n53 = 3.f - bindings->n11;
  bindings->n55 = bindings->n37 * bindings->n28;
  bindings->n54 = 9.f + bindings->n55;
  bindings->n52 = bindings->n53 - bindings->n54;
  bindings->n51 = bindings->n52 * bindings->n52;
  bindings->n43 = bindings->n44 + bindings->n51;
  bindings->n42 = 107.99999237060546875f - bindings->n43;
  bindings->n57 = 107.99999237060546875f + bindings->n43;
  bindings->n56 = bindings->n14 * bindings->n57;
  bindings->n41 = bindings->n42 / bindings->n56;
  bindings->n22 = bindings->n23 * bindings->n41;
  bindings->n9 = bindings->n10 + bindings->n22;
  bindings->n60 = bindings->n27 - bindings->n25;
  bindings->n59 = bindings->n60 - bindings->n9;
  bindings->n65 = bindings->n59 * bindings->n59;
  bindings->n68 = bindings->n35 - bindings->n50;
  bindings->n70 = bindings->n47 * bindings->n41;
  bindings->n69 = bindings->n48 + bindings->n70;
  bindings->n67 = bindings->n68 - bindings->n69;
  bindings->n66 = bindings->n67 * bindings->n67;
  bindings->n64 = bindings->n65 + bindings->n66;
  bindings->n73 = bindings->n38 - bindings->n55;
  bindings->n75 = bindings->n52 * bindings->n41;
  bindings->n74 = bindings->n53 + bindings->n75;
  bindings->n72 = bindings->n73 - bindings->n74;
  bindings->n71 = bindings->n72 * bindings->n72;
  bindings->n63 = bindings->n64 + bindings->n71;
  bindings->n62 = 26.999998092651367188f - bindings->n63;
  bindings->n77 = 26.999998092651367188f + bindings->n63;
  bindings->n76 = bindings->n14 * bindings->n77;
  bindings->n61 = bindings->n62 / bindings->n76;
  bindings->n58 = bindings->n59 * bindings->n61;
  bindings->n8 = bindings->n9 - bindings->n58;
  bindings->n81 = bindings->n24 - bindings->n22;
  bindings->n84 = bindings->n60 + bindings->n58;
  bindings->n83 = bindings->n81 - bindings->n84;
  bindings->n89 = bindings->n83 * bindings->n83;
  bindings->n92 = bindings->n49 - bindings->n70;
  bindings->n94 = bindings->n67 * bindings->n61;
  bindings->n93 = bindings->n68 + bindings->n94;
  bindings->n91 = bindings->n92 - bindings->n93;
  bindings->n90 = bindings->n91 * bindings->n91;
  bindings->n88 = bindings->n89 + bindings->n90;
  bindings->n97 = bindings->n54 - bindings->n75;
  bindings->n99 = bindings->n72 * bindings->n61;
  bindings->n98 = bindings->n73 + bindings->n99;
  bindings->n96 = bindings->n97 - bindings->n98;
  bindings->n95 = bindings->n96 * bindings->n96;
  bindings->n87 = bindings->n88 + bindings->n95;
  bindings->n86 = 26.999998092651367188f - bindings->n87;
  bindings->n101 = 26.999998092651367188f + bindings->n87;
  bindings->n100 = bindings->n14 * bindings->n101;
  bindings->n85 = bindings->n86 / bindings->n100;
  bindings->n82 = bindings->n83 * bindings->n85;
  bindings->n80 = bindings->n81 + bindings->n82;
  bindings->n79 = bindings->n8 - bindings->n80;
  bindings->n106 = bindings->n79 * bindings->n79;
  bindings->n109 = bindings->n69 - bindings->n94;
  bindings->n111 = bindings->n91 * bindings->n85;
  bindings->n110 = bindings->n92 + bindings->n111;
  bindings->n108 = bindings->n109 - bindings->n110;
  bindings->n107 = bindings->n108 * bindings->n108;
  bindings->n105 = bindings->n106 + bindings->n107;
  bindings->n114 = bindings->n74 - bindings->n99;
  bindings->n116 = bindings->n96 * bindings->n85;
  bindings->n115 = bindings->n97 + bindings->n116;
  bindings->n113 = bindings->n114 - bindings->n115;
  bindings->n112 = bindings->n113 * bindings->n113;
  bindings->n104 = bindings->n105 + bindings->n112;
  bindings->n103 = 107.99999237060546875f - bindings->n104;
  bindings->n118 = 107.99999237060546875f + bindings->n104;
  bindings->n117 = bindings->n14 * bindings->n118;
  bindings->n102 = bindings->n103 / bindings->n117;
  bindings->n78 = bindings->n79 * bindings->n102;
  bindings->n7 = bindings->n8 + bindings->n78;
  bindings->n121 = bindings->n84 - bindings->n82;
  bindings->n120 = bindings->n121 - bindings->n7;
  bindings->n126 = bindings->n120 * bindings->n120;
  bindings->n129 = bindings->n93 - bindings->n111;
  bindings->n131 = bindings->n108 * bindings->n102;
  bindings->n130 = bindings->n109 + bindings->n131;
  bindings->n128 = bindings->n129 - bindings->n130;
  bindings->n127 = bindings->n128 * bindings->n128;
  bindings->n125 = bindings->n126 + bindings->n127;
  bindings->n134 = bindings->n98 - bindings->n116;
  bindings->n136 = bindings->n113 * bindings->n102;
  bindings->n135 = bindings->n114 + bindings->n136;
  bindings->n133 = bindings->n134 - bindings->n135;
  bindings->n132 = bindings->n133 * bindings->n133;
  bindings->n124 = bindings->n125 + bindings->n132;
  bindings->n123 = 26.999998092651367188f - bindings->n124;
  bindings->n138 = 26.999998092651367188f + bindings->n124;
  bindings->n137 = bindings->n14 * bindings->n138;
  bindings->n122 = bindings->n123 / bindings->n137;
  bindings->n119 = bindings->n120 * bindings->n122;
  bindings->n6 = bindings->n7 - bindings->n119;
  bindings->n142 = bindings->n80 - bindings->n78;
  bindings->n145 = bindings->n121 + bindings->n119;
  bindings->n144 = bindings->n142 - bindings->n145;
  bindings->n150 = bindings->n144 * bindings->n144;
  bindings->n153 = bindings->n110 - bindings->n131;
  bindings->n155 = bindings->n128 * bindings->n122;
  bindings->n154 = bindings->n129 + bindings->n155;
  bindings->n152 = bindings->n153 - bindings->n154;
  bindings->n151 = bindings->n152 * bindings->n152;
  bindings->n149 = bindings->n150 + bindings->n151;
  bindings->n158 = bindings->n115 - bindings->n136;
  bindings->n160 = bindings->n133 * bindings->n122;
  bindings->n159 = bindings->n134 + bindings->n160;
  bindings->n157 = bindings->n158 - bindings->n159;
  bindings->n156 = bindings->n157 * bindings->n157;
  bindings->n148 = bindings->n149 + bindings->n156;
  bindings->n147 = 26.999998092651367188f - bindings->n148;
  bindings->n162 = 26.999998092651367188f + bindings->n148;
  bindings->n161 = bindings->n14 * bindings->n162;
  bindings->n146 = bindings->n147 / bindings->n161;
  bindings->n143 = bindings->n144 * bindings->n146;
  bindings->n141 = bindings->n142 + bindings->n143;
  bindings->n140 = bindings->n6 - bindings->n141;
  bindings->n167 = bindings->n140 * bindings->n140;
  bindings->n170 = bindings->n130 - bindings->n155;
  bindings->n172 = bindings->n152 * bindings->n146;
  bindings->n171 = bindings->n153 + bindings->n172;
  bindings->n169 = bindings->n170 - bindings->n171;
  bindings->n168 = bindings->n169 * bindings->n169;
  bindings->n166 = bindings->n167 + bindings->n168;
  bindings->n175 = bindings->n135 - bindings->n160;
  bindings->n177 = bindings->n157 * bindings->n146;
  bindings->n176 = bindings->n158 + bindings->n177;
  bindings->n174 = bindings->n175 - bindings->n176;
  bindings->n173 = bindings->n174 * bindings->n174;
  bindings->n165 = bindings->n166 + bindings->n173;
  bindings->n164 = 107.99999237060546875f - bindings->n165;
  bindings->n179 = 107.99999237060546875f + bindings->n165;
  bindings->n178 = bindings->n14 * bindings->n179;
  bindings->n163 = bindings->n164 / bindings->n178;
  bindings->n139 = bindings->n140 * bindings->n163;
  bindings->n5 = bindings->n6 + bindings->n139;
  bindings->n182 = bindings->n145 - bindings->n143;
  bindings->n181 = bindings->n182 - bindings->n5;
  bindings->n187 = bindings->n181 * bindings->n181;
  bindings->n190 = bindings->n154 - bindings->n172;
  bindings->n192 = bindings->n169 * bindings->n163;
  bindings->n191 = bindings->n170 + bindings->n192;
  bindings->n189 = bindings->n190 - bindings->n191;
  bindings->n188 = bindings->n189 * bindings->n189;
  bindings->n186 = bindings->n187 + bindings->n188;
  bindings->n195 = bindings->n159 - bindings->n177;
  bindings->n197 = bindings->n174 * bindings->n163;
  bindings->n196 = bindings->n175 + bindings->n197;
  bindings->n194 = bindings->n195 - bindings->n196;
  bindings->n193 = bindings->n194 * bindings->n194;
  bindings->n185 = bindings->n186 + bindings->n193;
  bindings->n184 = 26.999998092651367188f - bindings->n185;
  bindings->n199 = 26.999998092651367188f + bindings->n185;
  bindings->n198 = bindings->n14 * bindings->n199;
  bindings->n183 = bindings->n184 / bindings->n198;
  bindings->n180 = bindings->n181 * bindings->n183;
  bindings->n4 = bindings->n5 - bindings->n180;
  bindings->n203 = bindings->n141 - bindings->n139;
  bindings->n206 = bindings->n182 + bindings->n180;
  bindings->n205 = bindings->n203 - bindings->n206;
  bindings->n211 = bindings->n205 * bindings->n205;
  bindings->n214 = bindings->n171 - bindings->n192;
  bindings->n216 = bindings->n189 * bindings->n183;
  bindings->n215 = bindings->n190 + bindings->n216;
  bindings->n213 = bindings->n214 - bindings->n215;
  bindings->n212 = bindings->n213 * bindings->n213;
  bindings->n210 = bindings->n211 + bindings->n212;
  bindings->n219 = bindings->n176 - bindings->n197;
  bindings->n221 = bindings->n194 * bindings->n183;
  bindings->n220 = bindings->n195 + bindings->n221;
  bindings->n218 = bindings->n219 - bindings->n220;
  bindings->n217 = bindings->n218 * bindings->n218;
  bindings->n209 = bindings->n210 + bindings->n217;
  bindings->n208 = 26.999998092651367188f - bindings->n209;
  bindings->n223 = 26.999998092651367188f + bindings->n209;
  bindings->n222 = bindings->n14 * bindings->n223;
  bindings->n207 = bindings->n208 / bindings->n222;
  bindings->n204 = bindings->n205 * bindings->n207;
  bindings->n202 = bindings->n203 + bindings->n204;
  bindings->n201 = bindings->n4 - bindings->n202;
  bindings->n228 = bindings->n201 * bindings->n201;
  bindings->n231 = bindings->n191 - bindings->n216;
  bindings->n233 = bindings->n213 * bindings->n207;
  bindings->n232 = bindings->n214 + bindings->n233;
  bindings->n230 = bindings->n231 - bindings->n232;
  bindings->n229 = bindings->n230 * bindings->n230;
  bindings->n227 = bindings->n228 + bindings->n229;
  bindings->n236 = bindings->n196 - bindings->n221;
  bindings->n238 = bindings->n218 * bindings->n207;
  bindings->n237 = bindings->n219 + bindings->n238;
  bindings->n235 = bindings->n236 - bindings->n237;
  bindings->n234 = bindings->n235 * bindings->n235;
  bindings->n226 = bindings->n227 + bindings->n234;
  bindings->n225 = 107.99999237060546875f - bindings->n226;
  bindings->n240 = 107.99999237060546875f + bindings->n226;
  bindings->n239 = bindings->n14 * bindings->n240;
  bindings->n224 = bindings->n225 / bindings->n239;
  bindings->n200 = bindings->n201 * bindings->n224;
  bindings->n3 = bindings->n4 + bindings->n200;
  bindings->n243 = bindings->n206 - bindings->n204;
  bindings->n242 = bindings->n243 - bindings->n3;
  bindings->n248 = bindings->n242 * bindings->n242;
  bindings->n251 = bindings->n215 - bindings->n233;
  bindings->n253 = bindings->n230 * bindings->n224;
  bindings->n252 = bindings->n231 + bindings->n253;
  bindings->n250 = bindings->n251 - bindings->n252;
  bindings->n249 = bindings->n250 * bindings->n250;
  bindings->n247 = bindings->n248 + bindings->n249;
  bindings->n256 = bindings->n220 - bindings->n238;
  bindings->n258 = bindings->n235 * bindings->n224;
  bindings->n257 = bindings->n236 + bindings->n258;
  bindings->n255 = bindings->n256 - bindings->n257;
  bindings->n254 = bindings->n255 * bindings->n255;
  bindings->n246 = bindings->n247 + bindings->n254;
  bindings->n245 = 26.999998092651367188f - bindings->n246;
  bindings->n260 = 26.999998092651367188f + bindings->n246;
  bindings->n259 = bindings->n14 * bindings->n260;
  bindings->n244 = bindings->n245 / bindings->n259;
  bindings->n241 = bindings->n242 * bindings->n244;
  bindings->n2 = bindings->n3 - bindings->n241;
  bindings->n264 = bindings->n202 - bindings->n200;
  bindings->n267 = bindings->n243 + bindings->n241;
  bindings->n266 = bindings->n264 - bindings->n267;
  bindings->n272 = bindings->n266 * bindings->n266;
  bindings->n275 = bindings->n232 - bindings->n253;
  bindings->n277 = bindings->n250 * bindings->n244;
  bindings->n276 = bindings->n251 + bindings->n277;
  bindings->n274 = bindings->n275 - bindings->n276;
  bindings->n273 = bindings->n274 * bindings->n274;
  bindings->n271 = bindings->n272 + bindings->n273;
  bindings->n280 = bindings->n237 - bindings->n258;
  bindings->n282 = bindings->n255 * bindings->n244;
  bindings->n281 = bindings->n256 + bindings->n282;
  bindings->n279 = bindings->n280 - bindings->n281;
  bindings->n278 = bindings->n279 * bindings->n279;
  bindings->n270 = bindings->n271 + bindings->n278;
  bindings->n269 = 26.999998092651367188f - bindings->n270;
  bindings->n284 = 26.999998092651367188f + bindings->n270;
  bindings->n283 = bindings->n14 * bindings->n284;
  bindings->n268 = bindings->n269 / bindings->n283;
  bindings->n265 = bindings->n266 * bindings->n268;
  bindings->n263 = bindings->n264 + bindings->n265;
  bindings->n262 = bindings->n2 - bindings->n263;
  bindings->n289 = bindings->n262 * bindings->n262;
  bindings->n292 = bindings->n252 - bindings->n277;
  bindings->n294 = bindings->n274 * bindings->n268;
  bindings->n293 = bindings->n275 + bindings->n294;
  bindings->n291 = bindings->n292 - bindings->n293;
  bindings->n290 = bindings->n291 * bindings->n291;
  bindings->n288 = bindings->n289 + bindings->n290;
  bindings->n297 = bindings->n257 - bindings->n282;
  bindings->n299 = bindings->n279 * bindings->n268;
  bindings->n298 = bindings->n280 + bindings->n299;
  bindings->n296 = bindings->n297 - bindings->n298;
  bindings->n295 = bindings->n296 * bindings->n296;
  bindings->n287 = bindings->n288 + bindings->n295;
  bindings->n286 = 107.99999237060546875f - bindings->n287;
  bindings->n301 = 107.99999237060546875f + bindings->n287;
  bindings->n300 = bindings->n14 * bindings->n301;
  bindings->n285 = bindings->n286 / bindings->n300;
  bindings->n261 = bindings->n262 * bindings->n285;
  bindings->n1 = bindings->n2 + bindings->n261;
  bindings->n0 = ((double) bindings->n1);
  return bindings->n0;
}

int main(int argc, char **argv) {
  cl_platform_id platform;
  cl_device_id device;
  cl_context ctx;
  cl_program prog;
  cl_int errcode;
  cl_command_queue cq;
  cl_kernel kern;
  const char *opencl_code_ptr = opencl_code;
  size_t opencl_code_len = sizeof(opencl_code)-1;
  char flags[64];

  struct CPbinding host_bindings, dev_bindings;
  float kLST;
  cl_mem buf_bindings, buf_kLST;

  if (clGetPlatformIDs(1, &platform, NULL) != CL_SUCCESS)
    return 1;

  if (clGetDeviceIDs(platform, CL_DEVICE_TYPE_DEFAULT, 1, &device, NULL) != CL_SUCCESS)
    return 2;

  ctx = clCreateContext(NULL, 1, &device, NULL, NULL, &errcode);
  if (!ctx)
    return 3;

  prog = clCreateProgramWithSource(ctx, 1, &opencl_code_ptr, &opencl_code_len, &errcode);
  if (!prog)
    return 4;

  sprintf(flags, "-D HOST_SIZEOF_CPBINDING=%lu", (unsigned long) sizeof(struct CPbinding));

  if (clBuildProgram(prog, 1, &device, flags, NULL, NULL) != CL_SUCCESS) {
    size_t log_size;
    char *log;
    if (clGetProgramBuildInfo(prog, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size) != CL_SUCCESS)
      return 5;
    log = malloc(log_size);
    if (clGetProgramBuildInfo(prog, device, CL_PROGRAM_BUILD_LOG, log_size, log, NULL) != CL_SUCCESS)
      return 6;
    puts(log);
    return 7;
  }

  cq = clCreateCommandQueue(ctx, device, 0, &errcode);
  if (!cq)
    return 8;

  kern = clCreateKernel(prog, "CPeval", &errcode);
  if (!kern)
    return 9;

  buf_bindings = clCreateBuffer(ctx, CL_MEM_READ_WRITE, sizeof(struct CPbinding), 0, &errcode);
  if (!buf_bindings) {
    printf("%d\n", errcode);
    return 95;
  }
  if (clSetKernelArg(kern, 0, sizeof(cl_mem), &buf_bindings) != CL_SUCCESS)
    return 10;

  buf_kLST = clCreateBuffer(ctx, CL_MEM_READ_ONLY, sizeof(float), 0, &errcode);
  if (!buf_kLST) {
    printf("%d\n", errcode);
    return 105;
  }
  kLST = 123.f;
  if ((errcode = clEnqueueWriteBuffer(cq, buf_kLST, CL_TRUE, 0, sizeof(float), &kLST, 0, NULL, NULL)) != CL_SUCCESS) {
    printf("%d\n", errcode);
    return 11;
  }
  if (clSetKernelArg(kern, 1, sizeof(cl_mem), &buf_kLST) != CL_SUCCESS)
    return 12;

  if (clEnqueueTask(cq, kern, 0, NULL, NULL) != CL_SUCCESS)
    return 13;

  if (clFinish(cq) != CL_SUCCESS)
    return 14;

  if (clEnqueueReadBuffer(cq, buf_bindings, CL_TRUE, 0, sizeof(struct CPbinding), &dev_bindings, 0, NULL, NULL) != CL_SUCCESS)
    return 15;

  CPeval(&host_bindings, (char *) &kLST);

  printf("%.20f / %.20f\n", host_bindings.n0, dev_bindings.n0);

  return 0;
}
