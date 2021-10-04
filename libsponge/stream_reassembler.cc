#include "stream_reassembler.hh"

// Dummy implementation of a stream reassembler.

// For Lab 1, please replace with a real implementation that passes the
// automated checks run by `make check_lab1`.

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity) : _output(capacity), _capacity(capacity) {}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const string &data, const size_t index, const bool eof) {
    if (index > _assembled_tail_index+_output.remaining_capacity()){
        return;
    }
    if (index+data.size()<_assembled_tail_index){
        if (eof&&empty()){
            _output.end_input();
        }
        return;
    }
    bool flag  = true;
    if (index + data.size()>_assembled_tail_index+_output.remaining_capacity()){
        flag = false;
    }
    for(size_t i = index;i<index+data.size()&&i<_assembled_tail_index+_output.remaining_capacity();i++){
        if (i>=_assembled_tail_index&&index2byte.find(i)==index2byte.end()){
            index2byte[i]=data[i-index];
            _unassembled_bytes++;
        }
    }
    string str = "";
    for(size_t i=_assembled_tail_index;index2byte.find(i)!=index2byte.end();i++){
        str+=index2byte[i];
        index2byte.erase(i);
        _assembled_tail_index++;
        _unassembled_bytes--;
    }
    _output.write(str);
    if (flag && eof) {
        _eof = true;
    }
    if (_eof && empty()) {
        _output.end_input();
    }
}

size_t StreamReassembler::unassembled_bytes() const { return {_unassembled_bytes}; }

bool StreamReassembler::empty() const { return {unassembled_bytes()==0}; }
