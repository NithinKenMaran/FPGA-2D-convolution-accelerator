#include <systemc>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <stdint.h>
#include "SysCFileHandler.h"
#include "ap_int.h"
#include "ap_fixed.h"
#include <complex>
#include <stdbool.h>
#include "autopilot_cbe.h"
#include "hls_stream.h"
#include "hls_half.h"
#include "hls_signal_handler.h"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

// wrapc file define:
#define AUTOTB_TVIN_in_stream_V_data_V "../tv/cdatafile/c.conv2d_stream.autotvin_in_stream_V_data_V.dat"
#define AUTOTB_TVOUT_in_stream_V_data_V "../tv/cdatafile/c.conv2d_stream.autotvout_in_stream_V_data_V.dat"
#define AUTOTB_TVIN_in_stream_V_keep_V "../tv/cdatafile/c.conv2d_stream.autotvin_in_stream_V_keep_V.dat"
#define AUTOTB_TVOUT_in_stream_V_keep_V "../tv/cdatafile/c.conv2d_stream.autotvout_in_stream_V_keep_V.dat"
#define AUTOTB_TVIN_in_stream_V_strb_V "../tv/cdatafile/c.conv2d_stream.autotvin_in_stream_V_strb_V.dat"
#define AUTOTB_TVOUT_in_stream_V_strb_V "../tv/cdatafile/c.conv2d_stream.autotvout_in_stream_V_strb_V.dat"
#define AUTOTB_TVIN_in_stream_V_last_V "../tv/cdatafile/c.conv2d_stream.autotvin_in_stream_V_last_V.dat"
#define AUTOTB_TVOUT_in_stream_V_last_V "../tv/cdatafile/c.conv2d_stream.autotvout_in_stream_V_last_V.dat"
#define WRAPC_STREAM_SIZE_IN_in_stream_V_data_V "../tv/stream_size/stream_size_in_in_stream_V_data_V.dat"
#define WRAPC_STREAM_INGRESS_STATUS_in_stream_V_data_V "../tv/stream_size/stream_ingress_status_in_stream_V_data_V.dat"
#define WRAPC_STREAM_SIZE_IN_in_stream_V_keep_V "../tv/stream_size/stream_size_in_in_stream_V_keep_V.dat"
#define WRAPC_STREAM_INGRESS_STATUS_in_stream_V_keep_V "../tv/stream_size/stream_ingress_status_in_stream_V_keep_V.dat"
#define WRAPC_STREAM_SIZE_IN_in_stream_V_strb_V "../tv/stream_size/stream_size_in_in_stream_V_strb_V.dat"
#define WRAPC_STREAM_INGRESS_STATUS_in_stream_V_strb_V "../tv/stream_size/stream_ingress_status_in_stream_V_strb_V.dat"
#define WRAPC_STREAM_SIZE_IN_in_stream_V_last_V "../tv/stream_size/stream_size_in_in_stream_V_last_V.dat"
#define WRAPC_STREAM_INGRESS_STATUS_in_stream_V_last_V "../tv/stream_size/stream_ingress_status_in_stream_V_last_V.dat"
// wrapc file define:
#define AUTOTB_TVIN_out_stream_V_data_V "../tv/cdatafile/c.conv2d_stream.autotvin_out_stream_V_data_V.dat"
#define AUTOTB_TVOUT_out_stream_V_data_V "../tv/cdatafile/c.conv2d_stream.autotvout_out_stream_V_data_V.dat"
#define AUTOTB_TVIN_out_stream_V_keep_V "../tv/cdatafile/c.conv2d_stream.autotvin_out_stream_V_keep_V.dat"
#define AUTOTB_TVOUT_out_stream_V_keep_V "../tv/cdatafile/c.conv2d_stream.autotvout_out_stream_V_keep_V.dat"
#define AUTOTB_TVIN_out_stream_V_strb_V "../tv/cdatafile/c.conv2d_stream.autotvin_out_stream_V_strb_V.dat"
#define AUTOTB_TVOUT_out_stream_V_strb_V "../tv/cdatafile/c.conv2d_stream.autotvout_out_stream_V_strb_V.dat"
#define AUTOTB_TVIN_out_stream_V_last_V "../tv/cdatafile/c.conv2d_stream.autotvin_out_stream_V_last_V.dat"
#define AUTOTB_TVOUT_out_stream_V_last_V "../tv/cdatafile/c.conv2d_stream.autotvout_out_stream_V_last_V.dat"
#define WRAPC_STREAM_SIZE_OUT_out_stream_V_data_V "../tv/stream_size/stream_size_out_out_stream_V_data_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_out_stream_V_data_V "../tv/stream_size/stream_egress_status_out_stream_V_data_V.dat"
#define WRAPC_STREAM_SIZE_OUT_out_stream_V_keep_V "../tv/stream_size/stream_size_out_out_stream_V_keep_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_out_stream_V_keep_V "../tv/stream_size/stream_egress_status_out_stream_V_keep_V.dat"
#define WRAPC_STREAM_SIZE_OUT_out_stream_V_strb_V "../tv/stream_size/stream_size_out_out_stream_V_strb_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_out_stream_V_strb_V "../tv/stream_size/stream_egress_status_out_stream_V_strb_V.dat"
#define WRAPC_STREAM_SIZE_OUT_out_stream_V_last_V "../tv/stream_size/stream_size_out_out_stream_V_last_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_out_stream_V_last_V "../tv/stream_size/stream_egress_status_out_stream_V_last_V.dat"
// wrapc file define:
#define AUTOTB_TVIN_k00 "../tv/cdatafile/c.conv2d_stream.autotvin_k00.dat"
#define AUTOTB_TVOUT_k00 "../tv/cdatafile/c.conv2d_stream.autotvout_k00.dat"
// wrapc file define:
#define AUTOTB_TVIN_k01 "../tv/cdatafile/c.conv2d_stream.autotvin_k01.dat"
#define AUTOTB_TVOUT_k01 "../tv/cdatafile/c.conv2d_stream.autotvout_k01.dat"
// wrapc file define:
#define AUTOTB_TVIN_k02 "../tv/cdatafile/c.conv2d_stream.autotvin_k02.dat"
#define AUTOTB_TVOUT_k02 "../tv/cdatafile/c.conv2d_stream.autotvout_k02.dat"
// wrapc file define:
#define AUTOTB_TVIN_k10 "../tv/cdatafile/c.conv2d_stream.autotvin_k10.dat"
#define AUTOTB_TVOUT_k10 "../tv/cdatafile/c.conv2d_stream.autotvout_k10.dat"
// wrapc file define:
#define AUTOTB_TVIN_k11 "../tv/cdatafile/c.conv2d_stream.autotvin_k11.dat"
#define AUTOTB_TVOUT_k11 "../tv/cdatafile/c.conv2d_stream.autotvout_k11.dat"
// wrapc file define:
#define AUTOTB_TVIN_k12 "../tv/cdatafile/c.conv2d_stream.autotvin_k12.dat"
#define AUTOTB_TVOUT_k12 "../tv/cdatafile/c.conv2d_stream.autotvout_k12.dat"
// wrapc file define:
#define AUTOTB_TVIN_k20 "../tv/cdatafile/c.conv2d_stream.autotvin_k20.dat"
#define AUTOTB_TVOUT_k20 "../tv/cdatafile/c.conv2d_stream.autotvout_k20.dat"
// wrapc file define:
#define AUTOTB_TVIN_k21 "../tv/cdatafile/c.conv2d_stream.autotvin_k21.dat"
#define AUTOTB_TVOUT_k21 "../tv/cdatafile/c.conv2d_stream.autotvout_k21.dat"
// wrapc file define:
#define AUTOTB_TVIN_k22 "../tv/cdatafile/c.conv2d_stream.autotvin_k22.dat"
#define AUTOTB_TVOUT_k22 "../tv/cdatafile/c.conv2d_stream.autotvout_k22.dat"

#define INTER_TCL "../tv/cdatafile/ref.tcl"

// tvout file define:
#define AUTOTB_TVOUT_PC_in_stream_V_data_V "../tv/rtldatafile/rtl.conv2d_stream.autotvout_in_stream_V_data_V.dat"
#define AUTOTB_TVOUT_PC_in_stream_V_keep_V "../tv/rtldatafile/rtl.conv2d_stream.autotvout_in_stream_V_keep_V.dat"
#define AUTOTB_TVOUT_PC_in_stream_V_strb_V "../tv/rtldatafile/rtl.conv2d_stream.autotvout_in_stream_V_strb_V.dat"
#define AUTOTB_TVOUT_PC_in_stream_V_last_V "../tv/rtldatafile/rtl.conv2d_stream.autotvout_in_stream_V_last_V.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_out_stream_V_data_V "../tv/rtldatafile/rtl.conv2d_stream.autotvout_out_stream_V_data_V.dat"
#define AUTOTB_TVOUT_PC_out_stream_V_keep_V "../tv/rtldatafile/rtl.conv2d_stream.autotvout_out_stream_V_keep_V.dat"
#define AUTOTB_TVOUT_PC_out_stream_V_strb_V "../tv/rtldatafile/rtl.conv2d_stream.autotvout_out_stream_V_strb_V.dat"
#define AUTOTB_TVOUT_PC_out_stream_V_last_V "../tv/rtldatafile/rtl.conv2d_stream.autotvout_out_stream_V_last_V.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_k00 "../tv/rtldatafile/rtl.conv2d_stream.autotvout_k00.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_k01 "../tv/rtldatafile/rtl.conv2d_stream.autotvout_k01.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_k02 "../tv/rtldatafile/rtl.conv2d_stream.autotvout_k02.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_k10 "../tv/rtldatafile/rtl.conv2d_stream.autotvout_k10.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_k11 "../tv/rtldatafile/rtl.conv2d_stream.autotvout_k11.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_k12 "../tv/rtldatafile/rtl.conv2d_stream.autotvout_k12.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_k20 "../tv/rtldatafile/rtl.conv2d_stream.autotvout_k20.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_k21 "../tv/rtldatafile/rtl.conv2d_stream.autotvout_k21.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_k22 "../tv/rtldatafile/rtl.conv2d_stream.autotvout_k22.dat"

class INTER_TCL_FILE {
  public:
INTER_TCL_FILE(const char* name) {
  mName = name; 
  in_stream_V_data_V_depth = 0;
  in_stream_V_keep_V_depth = 0;
  in_stream_V_strb_V_depth = 0;
  in_stream_V_last_V_depth = 0;
  out_stream_V_data_V_depth = 0;
  out_stream_V_keep_V_depth = 0;
  out_stream_V_strb_V_depth = 0;
  out_stream_V_last_V_depth = 0;
  k00_depth = 0;
  k01_depth = 0;
  k02_depth = 0;
  k10_depth = 0;
  k11_depth = 0;
  k12_depth = 0;
  k20_depth = 0;
  k21_depth = 0;
  k22_depth = 0;
  trans_num =0;
}
~INTER_TCL_FILE() {
  mFile.open(mName);
  if (!mFile.good()) {
    cout << "Failed to open file ref.tcl" << endl;
    exit (1); 
  }
  string total_list = get_depth_list();
  mFile << "set depth_list {\n";
  mFile << total_list;
  mFile << "}\n";
  mFile << "set trans_num "<<trans_num<<endl;
  mFile.close();
}
string get_depth_list () {
  stringstream total_list;
  total_list << "{in_stream_V_data_V " << in_stream_V_data_V_depth << "}\n";
  total_list << "{in_stream_V_keep_V " << in_stream_V_keep_V_depth << "}\n";
  total_list << "{in_stream_V_strb_V " << in_stream_V_strb_V_depth << "}\n";
  total_list << "{in_stream_V_last_V " << in_stream_V_last_V_depth << "}\n";
  total_list << "{out_stream_V_data_V " << out_stream_V_data_V_depth << "}\n";
  total_list << "{out_stream_V_keep_V " << out_stream_V_keep_V_depth << "}\n";
  total_list << "{out_stream_V_strb_V " << out_stream_V_strb_V_depth << "}\n";
  total_list << "{out_stream_V_last_V " << out_stream_V_last_V_depth << "}\n";
  total_list << "{k00 " << k00_depth << "}\n";
  total_list << "{k01 " << k01_depth << "}\n";
  total_list << "{k02 " << k02_depth << "}\n";
  total_list << "{k10 " << k10_depth << "}\n";
  total_list << "{k11 " << k11_depth << "}\n";
  total_list << "{k12 " << k12_depth << "}\n";
  total_list << "{k20 " << k20_depth << "}\n";
  total_list << "{k21 " << k21_depth << "}\n";
  total_list << "{k22 " << k22_depth << "}\n";
  return total_list.str();
}
void set_num (int num , int* class_num) {
  (*class_num) = (*class_num) > num ? (*class_num) : num;
}
void set_string(std::string list, std::string* class_list) {
  (*class_list) = list;
}
  public:
    int in_stream_V_data_V_depth;
    int in_stream_V_keep_V_depth;
    int in_stream_V_strb_V_depth;
    int in_stream_V_last_V_depth;
    int out_stream_V_data_V_depth;
    int out_stream_V_keep_V_depth;
    int out_stream_V_strb_V_depth;
    int out_stream_V_last_V_depth;
    int k00_depth;
    int k01_depth;
    int k02_depth;
    int k10_depth;
    int k11_depth;
    int k12_depth;
    int k20_depth;
    int k21_depth;
    int k22_depth;
    int trans_num;
  private:
    ofstream mFile;
    const char* mName;
};

static void RTLOutputCheckAndReplacement(std::string &AESL_token, std::string PortName) {
  bool no_x = false;
  bool err = false;

  no_x = false;
  // search and replace 'X' with '0' from the 3rd char of token
  while (!no_x) {
    size_t x_found = AESL_token.find('X', 0);
    if (x_found != string::npos) {
      if (!err) { 
        cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port" 
             << PortName << ", possible cause: There are uninitialized variables in the C design."
             << endl; 
        err = true;
      }
      AESL_token.replace(x_found, 1, "0");
    } else
      no_x = true;
  }
  no_x = false;
  // search and replace 'x' with '0' from the 3rd char of token
  while (!no_x) {
    size_t x_found = AESL_token.find('x', 2);
    if (x_found != string::npos) {
      if (!err) { 
        cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' on port" 
             << PortName << ", possible cause: There are uninitialized variables in the C design."
             << endl; 
        err = true;
      }
      AESL_token.replace(x_found, 1, "0");
    } else
      no_x = true;
  }
}
struct __cosim_s4__ { char data[4]; };
extern "C" void conv2d_stream_hw_stub_wrapper(volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, __cosim_s4__*, __cosim_s4__*, __cosim_s4__*, __cosim_s4__*, __cosim_s4__*, __cosim_s4__*, __cosim_s4__*, __cosim_s4__*, __cosim_s4__*);

extern "C" void apatb_conv2d_stream_hw(volatile void * __xlx_apatb_param_in_stream_V_data_V, volatile void * __xlx_apatb_param_in_stream_V_keep_V, volatile void * __xlx_apatb_param_in_stream_V_strb_V, volatile void * __xlx_apatb_param_in_stream_V_last_V, volatile void * __xlx_apatb_param_out_stream_V_data_V, volatile void * __xlx_apatb_param_out_stream_V_keep_V, volatile void * __xlx_apatb_param_out_stream_V_strb_V, volatile void * __xlx_apatb_param_out_stream_V_last_V, __cosim_s4__* __xlx_apatb_param_k00, __cosim_s4__* __xlx_apatb_param_k01, __cosim_s4__* __xlx_apatb_param_k02, __cosim_s4__* __xlx_apatb_param_k10, __cosim_s4__* __xlx_apatb_param_k11, __cosim_s4__* __xlx_apatb_param_k12, __cosim_s4__* __xlx_apatb_param_k20, __cosim_s4__* __xlx_apatb_param_k21, __cosim_s4__* __xlx_apatb_param_k22) {
  refine_signal_handler();
  fstream wrapc_switch_file_token;
  wrapc_switch_file_token.open(".hls_cosim_wrapc_switch.log");
  int AESL_i;
  if (wrapc_switch_file_token.good())
  {

    CodeState = ENTER_WRAPC_PC;
    static unsigned AESL_transaction_pc = 0;
    string AESL_token;
    string AESL_num;long __xlx_apatb_param_in_stream_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_in_stream_V_data_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_in_stream_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_in_stream_stream_buf_final_size; ++i) {
((hls::stream<int>*)__xlx_apatb_param_in_stream_V_data_V)->read();
((hls::stream<char>*)__xlx_apatb_param_in_stream_V_keep_V)->read();
((hls::stream<char>*)__xlx_apatb_param_in_stream_V_strb_V)->read();
((hls::stream<char>*)__xlx_apatb_param_in_stream_V_last_V)->read();
}
{unsigned xlx_stream_out_stream_size = 0;

          std::vector<sc_bv<32> > out_stream_V_data_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_out_stream_V_data_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<32> > out_stream_V_data_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "out_stream");
  
            // push token into output port buffer
            if (AESL_token != "") {
              out_stream_V_data_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_out_stream_size=out_stream_V_data_V_pc_buffer.size();
out_stream_V_data_V_pc_buffer_Copy=out_stream_V_data_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
          std::vector<sc_bv<32> > out_stream_V_keep_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_out_stream_V_keep_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<32> > out_stream_V_keep_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "out_stream");
  
            // push token into output port buffer
            if (AESL_token != "") {
              out_stream_V_keep_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_out_stream_size=out_stream_V_keep_V_pc_buffer.size();
out_stream_V_keep_V_pc_buffer_Copy=out_stream_V_keep_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
          std::vector<sc_bv<32> > out_stream_V_strb_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_out_stream_V_strb_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<32> > out_stream_V_strb_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "out_stream");
  
            // push token into output port buffer
            if (AESL_token != "") {
              out_stream_V_strb_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_out_stream_size=out_stream_V_strb_V_pc_buffer.size();
out_stream_V_strb_V_pc_buffer_Copy=out_stream_V_strb_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
          std::vector<sc_bv<32> > out_stream_V_last_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_out_stream_V_last_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<32> > out_stream_V_last_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "out_stream");
  
            // push token into output port buffer
            if (AESL_token != "") {
              out_stream_V_last_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_out_stream_size=out_stream_V_last_V_pc_buffer.size();
out_stream_V_last_V_pc_buffer_Copy=out_stream_V_last_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (int j = 0, e = xlx_stream_out_stream_size; j != e; ++j) {
int xlx_stream_elt_data;
((int*)&xlx_stream_elt_data)[0] = out_stream_V_data_V_pc_buffer_Copy[j].to_int64();
((hls::stream<int>*)__xlx_apatb_param_out_stream_V_data_V)->write(xlx_stream_elt_data);
char xlx_stream_elt_keep;
((char*)&xlx_stream_elt_keep)[0] = out_stream_V_keep_V_pc_buffer_Copy[j].to_int64();
((hls::stream<char>*)__xlx_apatb_param_out_stream_V_keep_V)->write(xlx_stream_elt_keep);
char xlx_stream_elt_strb;
((char*)&xlx_stream_elt_strb)[0] = out_stream_V_strb_V_pc_buffer_Copy[j].to_int64();
((hls::stream<char>*)__xlx_apatb_param_out_stream_V_strb_V)->write(xlx_stream_elt_strb);
char xlx_stream_elt_last;
((char*)&xlx_stream_elt_last)[0] = out_stream_V_last_V_pc_buffer_Copy[j].to_uint64();
((hls::stream<char>*)__xlx_apatb_param_out_stream_V_last_V)->write(xlx_stream_elt_last);
}}
    AESL_transaction_pc++;
    return ;
  }
static unsigned AESL_transaction;
static AESL_FILE_HANDLER aesl_fh;
static INTER_TCL_FILE tcl_file(INTER_TCL);
std::vector<char> __xlx_sprintf_buffer(1024);
CodeState = ENTER_WRAPC;
//in_stream
aesl_fh.touch(AUTOTB_TVIN_in_stream_V_data_V);
aesl_fh.touch(AUTOTB_TVOUT_in_stream_V_data_V);
aesl_fh.touch(AUTOTB_TVIN_in_stream_V_keep_V);
aesl_fh.touch(AUTOTB_TVOUT_in_stream_V_keep_V);
aesl_fh.touch(AUTOTB_TVIN_in_stream_V_strb_V);
aesl_fh.touch(AUTOTB_TVOUT_in_stream_V_strb_V);
aesl_fh.touch(AUTOTB_TVIN_in_stream_V_last_V);
aesl_fh.touch(AUTOTB_TVOUT_in_stream_V_last_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_in_stream_V_data_V);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_data_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_in_stream_V_keep_V);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_keep_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_in_stream_V_strb_V);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_strb_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_in_stream_V_last_V);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_last_V);
//out_stream
aesl_fh.touch(AUTOTB_TVIN_out_stream_V_data_V);
aesl_fh.touch(AUTOTB_TVOUT_out_stream_V_data_V);
aesl_fh.touch(AUTOTB_TVIN_out_stream_V_keep_V);
aesl_fh.touch(AUTOTB_TVOUT_out_stream_V_keep_V);
aesl_fh.touch(AUTOTB_TVIN_out_stream_V_strb_V);
aesl_fh.touch(AUTOTB_TVOUT_out_stream_V_strb_V);
aesl_fh.touch(AUTOTB_TVIN_out_stream_V_last_V);
aesl_fh.touch(AUTOTB_TVOUT_out_stream_V_last_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_out_stream_V_data_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_out_stream_V_data_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_out_stream_V_keep_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_out_stream_V_keep_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_out_stream_V_strb_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_out_stream_V_strb_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_out_stream_V_last_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_out_stream_V_last_V);
//k00
aesl_fh.touch(AUTOTB_TVIN_k00);
aesl_fh.touch(AUTOTB_TVOUT_k00);
//k01
aesl_fh.touch(AUTOTB_TVIN_k01);
aesl_fh.touch(AUTOTB_TVOUT_k01);
//k02
aesl_fh.touch(AUTOTB_TVIN_k02);
aesl_fh.touch(AUTOTB_TVOUT_k02);
//k10
aesl_fh.touch(AUTOTB_TVIN_k10);
aesl_fh.touch(AUTOTB_TVOUT_k10);
//k11
aesl_fh.touch(AUTOTB_TVIN_k11);
aesl_fh.touch(AUTOTB_TVOUT_k11);
//k12
aesl_fh.touch(AUTOTB_TVIN_k12);
aesl_fh.touch(AUTOTB_TVOUT_k12);
//k20
aesl_fh.touch(AUTOTB_TVIN_k20);
aesl_fh.touch(AUTOTB_TVOUT_k20);
//k21
aesl_fh.touch(AUTOTB_TVIN_k21);
aesl_fh.touch(AUTOTB_TVOUT_k21);
//k22
aesl_fh.touch(AUTOTB_TVIN_k22);
aesl_fh.touch(AUTOTB_TVOUT_k22);
CodeState = DUMP_INPUTS;
// data
std::vector<int> __xlx_apatb_param_in_stream_V_data_V_stream_buf;
{
  while (!((hls::stream<int>*)__xlx_apatb_param_in_stream_V_data_V)->empty())
    __xlx_apatb_param_in_stream_V_data_V_stream_buf.push_back(((hls::stream<int>*)__xlx_apatb_param_in_stream_V_data_V)->read());
  for (int i = 0; i < __xlx_apatb_param_in_stream_V_data_V_stream_buf.size(); ++i)
    ((hls::stream<int>*)__xlx_apatb_param_in_stream_V_data_V)->write(__xlx_apatb_param_in_stream_V_data_V_stream_buf[i]);
  }
long __xlx_apatb_param_in_stream_stream_buf_size = ((hls::stream<int>*)__xlx_apatb_param_in_stream_V_data_V)->size();
// keep
std::vector<char> __xlx_apatb_param_in_stream_V_keep_V_stream_buf;
{
  while (!((hls::stream<char>*)__xlx_apatb_param_in_stream_V_keep_V)->empty())
    __xlx_apatb_param_in_stream_V_keep_V_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_in_stream_V_keep_V)->read());
  for (int i = 0; i < __xlx_apatb_param_in_stream_V_keep_V_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_in_stream_V_keep_V)->write(__xlx_apatb_param_in_stream_V_keep_V_stream_buf[i]);
  }
// strb
std::vector<char> __xlx_apatb_param_in_stream_V_strb_V_stream_buf;
{
  while (!((hls::stream<char>*)__xlx_apatb_param_in_stream_V_strb_V)->empty())
    __xlx_apatb_param_in_stream_V_strb_V_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_in_stream_V_strb_V)->read());
  for (int i = 0; i < __xlx_apatb_param_in_stream_V_strb_V_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_in_stream_V_strb_V)->write(__xlx_apatb_param_in_stream_V_strb_V_stream_buf[i]);
  }
// user
// last
std::vector<char> __xlx_apatb_param_in_stream_V_last_V_stream_buf;
{
  while (!((hls::stream<char>*)__xlx_apatb_param_in_stream_V_last_V)->empty())
    __xlx_apatb_param_in_stream_V_last_V_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_in_stream_V_last_V)->read());
  for (int i = 0; i < __xlx_apatb_param_in_stream_V_last_V_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_in_stream_V_last_V)->write(__xlx_apatb_param_in_stream_V_last_V_stream_buf[i]);
  }
// id
// dest
// data
std::vector<int> __xlx_apatb_param_out_stream_V_data_V_stream_buf;
long __xlx_apatb_param_out_stream_stream_buf_size = ((hls::stream<int>*)__xlx_apatb_param_out_stream_V_data_V)->size();
// keep
std::vector<char> __xlx_apatb_param_out_stream_V_keep_V_stream_buf;
// strb
std::vector<char> __xlx_apatb_param_out_stream_V_strb_V_stream_buf;
// user
// last
std::vector<char> __xlx_apatb_param_out_stream_V_last_V_stream_buf;
// id
// dest
// print k00 Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_k00, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_k00);

    std::string s(__xlx_tmp_lv.to_string(SC_HEX));
    aesl_fh.write(AUTOTB_TVIN_k00, s.append("\n")); 
  }
  tcl_file.set_num(1, &tcl_file.k00_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_k00, __xlx_sprintf_buffer.data());
}
// print k01 Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_k01, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_k01);

    std::string s(__xlx_tmp_lv.to_string(SC_HEX));
    aesl_fh.write(AUTOTB_TVIN_k01, s.append("\n")); 
  }
  tcl_file.set_num(1, &tcl_file.k01_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_k01, __xlx_sprintf_buffer.data());
}
// print k02 Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_k02, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_k02);

    std::string s(__xlx_tmp_lv.to_string(SC_HEX));
    aesl_fh.write(AUTOTB_TVIN_k02, s.append("\n")); 
  }
  tcl_file.set_num(1, &tcl_file.k02_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_k02, __xlx_sprintf_buffer.data());
}
// print k10 Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_k10, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_k10);

    std::string s(__xlx_tmp_lv.to_string(SC_HEX));
    aesl_fh.write(AUTOTB_TVIN_k10, s.append("\n")); 
  }
  tcl_file.set_num(1, &tcl_file.k10_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_k10, __xlx_sprintf_buffer.data());
}
// print k11 Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_k11, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_k11);

    std::string s(__xlx_tmp_lv.to_string(SC_HEX));
    aesl_fh.write(AUTOTB_TVIN_k11, s.append("\n")); 
  }
  tcl_file.set_num(1, &tcl_file.k11_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_k11, __xlx_sprintf_buffer.data());
}
// print k12 Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_k12, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_k12);

    std::string s(__xlx_tmp_lv.to_string(SC_HEX));
    aesl_fh.write(AUTOTB_TVIN_k12, s.append("\n")); 
  }
  tcl_file.set_num(1, &tcl_file.k12_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_k12, __xlx_sprintf_buffer.data());
}
// print k20 Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_k20, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_k20);

    std::string s(__xlx_tmp_lv.to_string(SC_HEX));
    aesl_fh.write(AUTOTB_TVIN_k20, s.append("\n")); 
  }
  tcl_file.set_num(1, &tcl_file.k20_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_k20, __xlx_sprintf_buffer.data());
}
// print k21 Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_k21, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_k21);

    std::string s(__xlx_tmp_lv.to_string(SC_HEX));
    aesl_fh.write(AUTOTB_TVIN_k21, s.append("\n")); 
  }
  tcl_file.set_num(1, &tcl_file.k21_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_k21, __xlx_sprintf_buffer.data());
}
// print k22 Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_k22, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_k22);

    std::string s(__xlx_tmp_lv.to_string(SC_HEX));
    aesl_fh.write(AUTOTB_TVIN_k22, s.append("\n")); 
  }
  tcl_file.set_num(1, &tcl_file.k22_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_k22, __xlx_sprintf_buffer.data());
}
CodeState = CALL_C_DUT;
conv2d_stream_hw_stub_wrapper(__xlx_apatb_param_in_stream_V_data_V, __xlx_apatb_param_in_stream_V_keep_V, __xlx_apatb_param_in_stream_V_strb_V, __xlx_apatb_param_in_stream_V_last_V, __xlx_apatb_param_out_stream_V_data_V, __xlx_apatb_param_out_stream_V_keep_V, __xlx_apatb_param_out_stream_V_strb_V, __xlx_apatb_param_out_stream_V_last_V, __xlx_apatb_param_k00, __xlx_apatb_param_k01, __xlx_apatb_param_k02, __xlx_apatb_param_k10, __xlx_apatb_param_k11, __xlx_apatb_param_k12, __xlx_apatb_param_k20, __xlx_apatb_param_k21, __xlx_apatb_param_k22);
CodeState = DUMP_OUTPUTS;
long __xlx_apatb_param_in_stream_stream_buf_final_size = __xlx_apatb_param_in_stream_stream_buf_size - ((hls::stream<int>*)__xlx_apatb_param_in_stream_V_data_V)->size();

  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_in_stream_V_data_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_in_stream_V_keep_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_in_stream_V_strb_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_in_stream_V_last_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_stream_stream_buf_final_size; j != e; ++j) {
sc_bv<32> __xlx_tmp_0_lv = ((int*)&__xlx_apatb_param_in_stream_V_data_V_stream_buf[j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_0_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVIN_in_stream_V_data_V, __xlx_sprintf_buffer.data());
sc_bv<4> __xlx_tmp_1_lv = ((char*)&__xlx_apatb_param_in_stream_V_keep_V_stream_buf[j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_1_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVIN_in_stream_V_keep_V, __xlx_sprintf_buffer.data());
sc_bv<4> __xlx_tmp_2_lv = ((char*)&__xlx_apatb_param_in_stream_V_strb_V_stream_buf[j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_2_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVIN_in_stream_V_strb_V, __xlx_sprintf_buffer.data());
sc_bv<1> __xlx_tmp_4_lv = ((char*)&__xlx_apatb_param_in_stream_V_last_V_stream_buf[j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_4_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVIN_in_stream_V_last_V, __xlx_sprintf_buffer.data());
}
tcl_file.set_num(__xlx_apatb_param_in_stream_stream_buf_final_size, &tcl_file.in_stream_V_data_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_in_stream_V_data_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_in_stream_stream_buf_final_size, &tcl_file.in_stream_V_keep_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_in_stream_V_keep_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_in_stream_stream_buf_final_size, &tcl_file.in_stream_V_strb_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_in_stream_V_strb_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_in_stream_stream_buf_final_size, &tcl_file.in_stream_V_last_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_in_stream_V_last_V, __xlx_sprintf_buffer.data());

// dump stream ingress status to file

// dump stream ingress status to file
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_data_V, __xlx_sprintf_buffer.data());
  if (__xlx_apatb_param_in_stream_stream_buf_final_size > 0) {
  long in_stream_V_data_V_stream_ingress_size = __xlx_apatb_param_in_stream_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_stream_V_data_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_data_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_stream_stream_buf_final_size; j != e; j++) {
    in_stream_V_data_V_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_stream_V_data_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_data_V, __xlx_sprintf_buffer.data());
  }
} else {
  long in_stream_V_data_V_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_stream_V_data_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_data_V, __xlx_sprintf_buffer.data());
}

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_data_V, __xlx_sprintf_buffer.data());
}
// dump stream ingress status to file
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_keep_V, __xlx_sprintf_buffer.data());
  if (__xlx_apatb_param_in_stream_stream_buf_final_size > 0) {
  long in_stream_V_keep_V_stream_ingress_size = __xlx_apatb_param_in_stream_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_stream_V_keep_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_keep_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_stream_stream_buf_final_size; j != e; j++) {
    in_stream_V_keep_V_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_stream_V_keep_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_keep_V, __xlx_sprintf_buffer.data());
  }
} else {
  long in_stream_V_keep_V_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_stream_V_keep_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_keep_V, __xlx_sprintf_buffer.data());
}

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_keep_V, __xlx_sprintf_buffer.data());
}
// dump stream ingress status to file
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_strb_V, __xlx_sprintf_buffer.data());
  if (__xlx_apatb_param_in_stream_stream_buf_final_size > 0) {
  long in_stream_V_strb_V_stream_ingress_size = __xlx_apatb_param_in_stream_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_stream_V_strb_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_strb_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_stream_stream_buf_final_size; j != e; j++) {
    in_stream_V_strb_V_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_stream_V_strb_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_strb_V, __xlx_sprintf_buffer.data());
  }
} else {
  long in_stream_V_strb_V_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_stream_V_strb_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_strb_V, __xlx_sprintf_buffer.data());
}

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_strb_V, __xlx_sprintf_buffer.data());
}
// dump stream ingress status to file
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_last_V, __xlx_sprintf_buffer.data());
  if (__xlx_apatb_param_in_stream_stream_buf_final_size > 0) {
  long in_stream_V_last_V_stream_ingress_size = __xlx_apatb_param_in_stream_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_stream_V_last_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_last_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_stream_stream_buf_final_size; j != e; j++) {
    in_stream_V_last_V_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_stream_V_last_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_last_V, __xlx_sprintf_buffer.data());
  }
} else {
  long in_stream_V_last_V_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_stream_V_last_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_last_V, __xlx_sprintf_buffer.data());
}

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_stream_V_last_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_stream_V_data_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_in_stream_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_stream_V_data_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_stream_V_data_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_stream_V_keep_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_in_stream_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_stream_V_keep_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_stream_V_keep_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_stream_V_strb_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_in_stream_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_stream_V_strb_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_stream_V_strb_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_stream_V_last_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_in_stream_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_stream_V_last_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_stream_V_last_V, __xlx_sprintf_buffer.data());
}
//********************** dump C output stream *******************
long __xlx_apatb_param_out_stream_stream_buf_final_size = ((hls::stream<int>*)__xlx_apatb_param_out_stream_V_data_V)->size() - __xlx_apatb_param_out_stream_stream_buf_size;
{
  while (!((hls::stream<int>*)__xlx_apatb_param_out_stream_V_data_V)->empty())
    __xlx_apatb_param_out_stream_V_data_V_stream_buf.push_back(((hls::stream<int>*)__xlx_apatb_param_out_stream_V_data_V)->read());
  for (int i = 0; i < __xlx_apatb_param_out_stream_V_data_V_stream_buf.size(); ++i)
    ((hls::stream<int>*)__xlx_apatb_param_out_stream_V_data_V)->write(__xlx_apatb_param_out_stream_V_data_V_stream_buf[i]);
  }
{
  while (!((hls::stream<char>*)__xlx_apatb_param_out_stream_V_keep_V)->empty())
    __xlx_apatb_param_out_stream_V_keep_V_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_out_stream_V_keep_V)->read());
  for (int i = 0; i < __xlx_apatb_param_out_stream_V_keep_V_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_out_stream_V_keep_V)->write(__xlx_apatb_param_out_stream_V_keep_V_stream_buf[i]);
  }
{
  while (!((hls::stream<char>*)__xlx_apatb_param_out_stream_V_strb_V)->empty())
    __xlx_apatb_param_out_stream_V_strb_V_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_out_stream_V_strb_V)->read());
  for (int i = 0; i < __xlx_apatb_param_out_stream_V_strb_V_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_out_stream_V_strb_V)->write(__xlx_apatb_param_out_stream_V_strb_V_stream_buf[i]);
  }
{
  while (!((hls::stream<char>*)__xlx_apatb_param_out_stream_V_last_V)->empty())
    __xlx_apatb_param_out_stream_V_last_V_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_out_stream_V_last_V)->read());
  for (int i = 0; i < __xlx_apatb_param_out_stream_V_last_V_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_out_stream_V_last_V)->write(__xlx_apatb_param_out_stream_V_last_V_stream_buf[i]);
  }

  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_out_stream_V_data_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_out_stream_V_keep_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_out_stream_V_strb_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_out_stream_V_last_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_out_stream_stream_buf_final_size; j != e; ++j) {
sc_bv<32> __xlx_tmp_0_lv = ((int*)&__xlx_apatb_param_out_stream_V_data_V_stream_buf[__xlx_apatb_param_out_stream_stream_buf_size+j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_0_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_out_stream_V_data_V, __xlx_sprintf_buffer.data());
sc_bv<4> __xlx_tmp_1_lv = ((char*)&__xlx_apatb_param_out_stream_V_keep_V_stream_buf[__xlx_apatb_param_out_stream_stream_buf_size+j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_1_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_out_stream_V_keep_V, __xlx_sprintf_buffer.data());
sc_bv<4> __xlx_tmp_2_lv = ((char*)&__xlx_apatb_param_out_stream_V_strb_V_stream_buf[__xlx_apatb_param_out_stream_stream_buf_size+j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_2_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_out_stream_V_strb_V, __xlx_sprintf_buffer.data());
sc_bv<1> __xlx_tmp_4_lv = ((char*)&__xlx_apatb_param_out_stream_V_last_V_stream_buf[__xlx_apatb_param_out_stream_stream_buf_size+j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_4_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_out_stream_V_last_V, __xlx_sprintf_buffer.data());
}
tcl_file.set_num(__xlx_apatb_param_out_stream_stream_buf_final_size, &tcl_file.out_stream_V_data_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_out_stream_V_data_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_out_stream_stream_buf_final_size, &tcl_file.out_stream_V_keep_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_out_stream_V_keep_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_out_stream_stream_buf_final_size, &tcl_file.out_stream_V_strb_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_out_stream_V_strb_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_out_stream_stream_buf_final_size, &tcl_file.out_stream_V_last_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_out_stream_V_last_V, __xlx_sprintf_buffer.data());
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_stream_V_data_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_out_stream_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_stream_V_data_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_stream_V_data_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_stream_V_keep_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_out_stream_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_stream_V_keep_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_stream_V_keep_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_stream_V_strb_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_out_stream_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_stream_V_strb_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_stream_V_strb_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_stream_V_last_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_out_stream_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_stream_V_last_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_stream_V_last_V, __xlx_sprintf_buffer.data());
}CodeState = DELETE_CHAR_BUFFERS;
AESL_transaction++;
tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
}
