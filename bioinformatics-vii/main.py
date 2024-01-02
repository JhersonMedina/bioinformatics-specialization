from Bio import SeqIO
import matplotlib.pyplot as plt 
import os

path = "UK-Genomes/UK-Genomes"
f = open("result.txt", "w")
total_squences = 0

codons = {
    'ATA':'I', 'ATC':'I', 'ATT':'I', 'ATG':'M',
    'ACA':'T', 'ACC':'T', 'ACG':'T', 'ACT':'T',
    'AAC':'N', 'AAT':'N', 'AAA':'K', 'AAG':'K',
    'AGC':'S', 'AGT':'S', 'AGA':'R', 'AGG':'R',
    'CTA':'L', 'CTC':'L', 'CTG':'L', 'CTT':'L',
    'CCA':'P', 'CCC':'P', 'CCG':'P', 'CCT':'P',
    'CAC':'H', 'CAT':'H', 'CAA':'Q', 'CAG':'Q',
    'CGA':'R', 'CGC':'R', 'CGG':'R', 'CGT':'R',
    'GTA':'V', 'GTC':'V', 'GTG':'V', 'GTT':'V',
    'GCA':'A', 'GCC':'A', 'GCG':'A', 'GCT':'A',
    'GAC':'D', 'GAT':'D', 'GAA':'E', 'GAG':'E',
    'GGA':'G', 'GGC':'G', 'GGG':'G', 'GGT':'G',
    'TCA':'S', 'TCC':'S', 'TCG':'S', 'TCT':'S',
    'TTC':'F', 'TTT':'F', 'TTA':'L', 'TTG':'L',
    'TAC':'Y', 'TAT':'Y', 'TAA':'_', 'TAG':'_',
    'TGC':'C', 'TGT':'C', 'TGA':'_', 'TGG':'W',
}

left = [1, 2, 3, 4] 
height = [0, 0, 0, 0] 

for root, dirs, files in os.walk(path):
    for _dir in dirs:
        for _file in os.listdir(path + "/" + _dir):
            if not _file.endswith('A.fasta'):
                continue
            
            file = path + "/" + _dir + "/" + _file

            fasta_sequences = SeqIO.parse(open(file),'fasta')
            for fasta in fasta_sequences:
                name, sequence = fasta.id, str(fasta.seq)

                total_squences += 1

                delta = 2040
                alpha = 1698
                omicron = 198

                is_variant = 0
                

                if (sequence[delta:delta+3] in codons and codons[sequence[delta:delta+3]] == 'R'):
                    height[0] += 1
                    is_variant = 1

                if (sequence[alpha:alpha+3] in codons and codons[sequence[alpha:alpha+3]] == 'D'):
                    height[1] += 1
                    is_variant = 1

                if (sequence[omicron:omicron+3] in codons and codons[sequence[omicron:omicron+3]] == 'V'):
                    height[2] += 1
                    is_variant = 1
                
                if (not is_variant):
                    height[3] += 1



tick_label = ['delta', 'alpha', 'omicron', "other"] 
for i in range(0, 4):
    height[i] = height[i]*100 / total_squences

plt.bar(left, height, tick_label = tick_label, 
        width = 0.8, color = ['red', 'green']) 
plt.xlabel('Variant') 
plt.ylabel('Percent') 
plt.title('Variant Frequency Percent') 
plt.show()