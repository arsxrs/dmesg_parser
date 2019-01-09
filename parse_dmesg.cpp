#include <string>
#include <iostream>
#include <fstream>

#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>

#include "dmesg.hh"
#include "avro/ValidSchema.hh"
#include "avro/Compiler.hh"
#include "avro/DataFile.hh"

using namespace boost::program_options;
using namespace std;
using namespace boost;


int program_options_handle(int argc, char* argv[], string &ifile, string &ofile);
c::pci_desc parse_pci_bus(vector <string> SplitVec);
string parse_description(vector <string> SplitVec);



int main(int argc, char* argv[])
{

    string ifile, ofile ;
    string line;
    vector <string> SplitVec;

    c::dmesg_parse schema_write;
    c::pci_desc pci_d;
   
    /*Handling input options */
    if(program_options_handle(argc, argv, ifile, ofile) != 0)
    {
        return -1;
    }

    ifstream in(ifile); //Must be some checking for file existing
    avro::ValidSchema schema;
    avro::compileJsonSchema(in, schema);

    avro::DataFileWriter<c::dmesg_parse> dfw(ofile.c_str(), schema);

    /*read every line from pipe of dmesg*/
    while ( getline (cin,line) )
    {
        if(!line.empty())
        {
            /*clear control caracters for reading timestamp*/
            erase_first(line, "[");
            erase_first(line, "]");
            trim(line);

            /*split every line for further parsing posibilities*/
            split(SplitVec, line, is_any_of(" "), token_compress_on);

             if (SplitVec.size() > 2)
             {
                 schema_write.time_label = SplitVec[0];
                 schema_write.group = SplitVec[1];
             
                if ( schema_write.group.compare("pci_bus") == 0)
                {
                    schema_write.description.set_pci_desc(parse_pci_bus(SplitVec));
                }
                else
                {
                    schema_write.description.set_string(parse_description(SplitVec));
                }
                dfw.write(schema_write);
            }
        }

    }
    dfw.close();

    /*Code for read and printing filled file*/
    // {
    //     avro::DataFileReader<c::dmesg_parse> dfr(ofile.c_str(), schema);
    //     c::dmesg_parse data_reader;

    //     while (dfr.read(data_reader)) 
    //     {
    //         std::cout << '(' << data_reader.time_label << ", " << data_reader.group << ", ";
            
    //         /*Switch between general description and pci_description*/
    //         if (data_reader.description.idx() == 0)
    //         {
    //              std::cout << data_reader.description.get_string() << ')' << endl;
    //         }
    //         else 
    //         {
    //             c::pci_desc read_pci_desc =  data_reader.description.get_pci_desc();
    //             std::cout <<  read_pci_desc.bus << ", " << read_pci_desc.recource << ", " << read_pci_desc.memory  << ')' << std::endl;
    //         }
    //     }
    // }

    return 0;
}


int program_options_handle(int argc, char* argv[], string &ifile, string &ofile)
{
    try
    {
        options_description desc("Allowed options");
        desc.add_options()
        ("help,h", "print usage message")
        ("schema,s", value(&ifile), "write source package list to <pathname>")
        ("output,o", value(&ofile), "pathname for output")
        ;


        variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);

        if (vm.count("help")) {
            cout << desc << "\n";
            return -1;
        }

        if (vm.count("schema")) {
            ifile = vm["schema"].as<string>();
        } else {
            cout << "Schema parameter is missing.\n";
            return -1;
        }

        if (vm.count("output")) {
            ofile = vm["output"].as<string>();
        } else {
            cout << "Output file parameter is missing.\n";
            return -1;
        }
    }
    catch(std::exception& e)
    {
        cerr << e.what() << "\n";
    }

    return 0;
}


/*Very simple pci_bus parser*/
c::pci_desc parse_pci_bus(vector <string> SplitVec)
{
    c::pci_desc pci_d;
    int i = 2; // start parsing after timestamp and dmesg_group

    pci_d.bus = SplitVec[i++];
    
    /*concatenate resource name */
    for(;(SplitVec[i].find("[") == string::npos) && (i < SplitVec.size()) ;i++)
        pci_d.recource   += " " + SplitVec[i];
    
    /*concatenate memory range description*/
    for(;i < SplitVec.size();i++)
        pci_d.memory += " " + SplitVec[i];

    return pci_d;
};


string parse_description(vector <string> SplitVec)
{
    string full_description;
    int i = 2; // start parsing after timestamp and dmesg_group

     /*concatenate full description*/
    for(; i < SplitVec.size(); i++)
        full_description += " "  + SplitVec[i];
    
    return full_description;
}