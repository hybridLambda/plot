/*
 * hybrid-Lambda is used to simulate gene trees given species network under 
 * coalescent process.
 * 
 * Copyright (C) 2010 -- 2014 Sha (Joe) Zhu
 * 
 * This file is part of hybrid-Lambda.
 * 
 * hybrid-Lambda is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "graph.hpp"
#include <iostream> // clog

enum FIGURE_OPTION { PLOT_DEFAULT, BRANCH, LABEL};
enum FIGURE_PROGRAM { NO_METHOD, LATEX, DOT };

class Figure{
    friend class HybridLambda;
    friend class HybridCoal;
    friend class PlotApp;
    #ifdef UNITTEST
    friend class TestFigure;
    #endif
    // Members
    string figure_file_prefix;
    FIGURE_PROGRAM method;
    FIGURE_OPTION option;    
    int argc_;
    int argc_i;
    char * const* argv_;
    valarray <int> x_node;
    vector <int> x_node_tmp;
    vector <size_t> x_node_tmp_index;
    ofstream figure_ofstream;
    string figure_file_suffix;
    string figure_file_name;
    GraphBuilder* graph;
    
    // Methods    
    Figure ( int argc, char * const* argv );
    ~Figure(){ if ( graph != NULL ) delete graph; }
    void plot( string net_str );
    void init();
    void initialize_method( FIGURE_PROGRAM program, string suffix);
    void check_option();
    void check_method();
    void finalize();
    void det_x_node ( );
    void x_node_shift();
    void plot_in_latex();
    void plot_in_dot( );
    void plot_core();
    void execute_dot(string method, string suffix);
    void edge_entry(string from, string to, size_t label, double bl, bool tip);

    /*! \brief Remove '#' signs and the gamma parameter from a string \return string */
    string rm_hash_sign( string in_str ){
        while ( int(in_str.find('#'))>0 && in_str.find('#')!=string::npos ) {
            size_t i = end_of_label_or_bl(in_str, in_str.find('#'));
            in_str.erase(in_str.find('#'),i-in_str.find('#')+1);
            //in_str.erase(in_str.find('#'),1);
        }
        return in_str;
    }

    /*! \brief Remove the '&' and '#' signs from a string \return string */
    string rm_and_hash_sign( string in_str ){
        return rm_hash_sign( rm_and_sign ( in_str ) );
    }

    string rm_and_sign( string in_str ){
        while ( int(in_str.find('&')) > 0 && in_str.find('&')!=string::npos) {
            in_str.erase(in_str.find('&'),1);
        }
        return in_str;
    }
};

class PlotApp{
    int argc_;
    int argc_i;
    char * const* argv_;
    string tmp_input_str;
    string net_str;
    string prefix;

    void print_help(){
        cout << "USAGE:" << endl;
        cout << "./plot -graph \"((1:1,2:1):1,3:2);\" -dot -branch" <<endl;
    }
    
    void init(){
        this->prefix  = "OUT";
        this->argc_i  = 1;
        //this->net_str = "";
    }
    
    void parse(){
        while (argc_i < argc_){	
            std::string argv_i(argv_[argc_i]);
            if ( argv_i == "-h" || argv_i == "-help" ){ print_help(); }
            else if ( argv_i =="-graph" ){ readNextStringto( this->tmp_input_str , this->argc_i, this->argc_,  this->argv_ );
                                           this->net_str = read_input_line(tmp_input_str.c_str());
                                          }
            else if ( argv_i =="-o" )    { readNextStringto( this->prefix , this->argc_i, this->argc_,  this->argv_ ); }
            else if ( argv_i =="-label" || argv_i =="-branch" || argv_i =="-dot" || argv_i =="-plot" ) { argc_i++; continue;}
            //else if ( argv_i == "-print" ){ this->print_tree_bool = true; }
            else { throw std::invalid_argument ( "Unknown flag:" + argv_i); }
            //else { cout <<"  need to change this !!!" << argv_i<<endl; argc_i++;continue; } // need to change this !!!
            argc_i++;
        }
    
    }
    void finalize(){
        Figure figure_para ( this->argc_, this->argv_ );
        figure_para.figure_file_prefix = this->prefix;
        figure_para.finalize();
        figure_para.plot( this->net_str );
    }
  
    string read_input_line(const char *inchar){
	string out_str;
    ifstream in_file( inchar );
	if (in_file.good())	getline ( in_file, out_str); 
	else{
		string dummy_str(inchar);
		if (dummy_str.find('(')!=string::npos && dummy_str.find(')')!=string::npos) out_str=dummy_str;
		else  throw std::invalid_argument("Invalid input file. " + string (inchar) );
	}
	in_file.close();			
    return 	out_str;
    }
  
  public:
    PlotApp ( int argc, char *argv[]) : argc_(argc), argv_(argv) {
        if ( argc_ == 1 ){
            print_help();
            return;
        }
            
        this->init();
        this->parse();
        this->finalize();
    }
    ~PlotApp (){}    
};

