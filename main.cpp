#include <bits/stdc++.h>

using namespace std;

int kartojimai=0;

map <char, vector<string>> aa_to_codon;
map <string, vector<string>> restriction_enzyme_sequences;
set<string> unsuitable_restriction_enzymes;

string aa_sequence;
int longest_restriction_enzyme=0, shortest_restriction_enzyme=INT_MAX;

void prepare_aa_to_codons()
{
    ifstream fin ("Codon_Table.txt");
    char aa;
    string codon, x;
    for(int i=0; i!=66; i++)
    {
        fin>>codon>>x>>x>>aa>>x;
        aa_to_codon[aa].push_back(codon);
    }
}

void prepare_restriction_enzymes()
{
    ifstream fin ("Restriction_Enzymes.txt");
    string enzyme_name, recognized_sequence_5, recognized_sequence_3,x;

    // the number of restriction enzymes
    for(int i=0; i!=4; i++)
    {
        fin>>enzyme_name>>x>>recognized_sequence_5>>x>>recognized_sequence_3;

        restriction_enzyme_sequences[recognized_sequence_5].push_back(enzyme_name);
        reverse(recognized_sequence_3.begin(),recognized_sequence_3.end());
        if(recognized_sequence_3!=recognized_sequence_5)
            restriction_enzyme_sequences[recognized_sequence_3].push_back(enzyme_name);

        int temporary=max(recognized_sequence_5.length(),recognized_sequence_3.length());
        longest_restriction_enzyme=max(longest_restriction_enzyme, temporary);
        temporary=min(recognized_sequence_5.length(),recognized_sequence_3.length());
        shortest_restriction_enzyme=min(shortest_restriction_enzyme, temporary);
    }

}


void construct_sequences(string current_sequence, int aa_position)
{

    if(current_sequence.length()<longest_restriction_enzyme+3 && aa_position!=aa_sequence.length())
        for(auto i: aa_to_codon[aa_sequence[aa_position]])
            construct_sequences(current_sequence+i,aa_position+1);

    else for(int i=0; i!=3; i++)
        {
            for(int j=shortest_restriction_enzyme; i+j<current_sequence.length(); j++)
            {
                string checked_sequence = current_sequence.substr(i,j);

                if(restriction_enzyme_sequences[checked_sequence].size()!=0)
                    unsuitable_restriction_enzymes.insert(checked_sequence);

            }
        }
}


int main()
{
    prepare_aa_to_codons();
    prepare_restriction_enzymes();
    cout<<"This program outputs which of enzymes in the Restriction_Enzymes.txt file cut all the possible DNA sequences for the inputed \n\nAmino acid sequnce input:\n";
    cin>>aa_sequence;


    for(int i=0; i<aa_sequence.length(); i++) construct_sequences("", i);

    set <string> checked;
    cout<<"\nUnsuitable restriction enzymes:\n";
    for( auto i:unsuitable_restriction_enzymes)
    {
        for(auto j:restriction_enzyme_sequences[i])
            checked.insert(j);

    }


    for(auto i: checked)
        cout<<i<<endl;





    return 0;
}
