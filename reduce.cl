#define OP_WARPSIZE 32

typedef enum {OP_READ, OP_WRITE, OP_RW, OP_INC, OP_MIN, OP_MAX} op_access;

inline void op_reduction( __global volatile float *dat_g, float dat_l, op_access reduction, __local float *temp)
{
  int tid = get_local_id( 0 );
  int d   = get_local_size( 0 )>>1; 

  barrier( CLK_LOCAL_MEM_FENCE );  // important to finish all previous activity

  temp[tid] = dat_l;

  size_t warpSize = OP_WARPSIZE;

  for ( ; d>warpSize; d>>=1 ) {
    barrier( CLK_LOCAL_MEM_FENCE );
    if ( tid<d ) {
      switch ( reduction ) {
      case OP_INC:
        temp[tid] = temp[tid] + temp[tid+d];
        break;
      case OP_MIN:
        if( temp[tid+d]<temp[tid] ) temp[tid] = temp[tid+d];
        break;
      case OP_MAX:
        if( temp[tid+d]>temp[tid] ) temp[tid] = temp[tid+d];
        break;
      }
    }
  }

  barrier( CLK_LOCAL_MEM_FENCE );

  __local volatile float *vtemp = temp;   // see Fermi compatibility guide 

  if ( tid<warpSize ) {
    for ( ; d>0; d>>=1 ) {
      barrier( CLK_LOCAL_MEM_FENCE );
      if ( tid<d ) {
        switch ( reduction ) {
        case OP_INC:
          vtemp[tid] = vtemp[tid] + vtemp[tid+d];
          break;
        case OP_MIN:
          if( vtemp[tid+d]<vtemp[tid] ) vtemp[tid] = vtemp[tid+d];
          break;
        case OP_MAX:
          if( vtemp[tid+d]>vtemp[tid] ) vtemp[tid] = vtemp[tid+d];
          break;
        }
      }
    }
  }

  if ( tid==0 ) {
    switch ( reduction ) {
    case OP_INC:
      *dat_g = *dat_g + vtemp[0];
      break;
    case OP_MIN:
      if( temp[0]<*dat_g ) *dat_g = vtemp[0];
      break;
    case OP_MAX:
      if( temp[0]>*dat_g ) *dat_g = vtemp[0];
      break;
    }
  }

}

__kernel void reduce(__global float *out, __global float *in,
                     unsigned reduction, __local float *temp) {
  op_reduction(&out[get_group_id(0)], in[get_global_id(0)], reduction, temp);
}
