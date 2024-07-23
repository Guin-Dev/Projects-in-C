def process_file(input_file, output_file):
    try:
        with open(input_file, 'r', encoding='utf-8') as infile, open(output_file, 'w', encoding='utf-8') as outfile:
            for line in infile:
                line = line.strip()  # Remove espaços em branco no início e no fim da linha
                formatted_line = f'"{line}",\n'
                outfile.write(formatted_line)
        print(f"Arquivo processado com sucesso. Saída salva em {output_file}")
    except FileNotFoundError:
        print(f"Erro: O arquivo {input_file} não foi encontrado.")
    except Exception as e:
        print(f"Erro inesperado: {e}")

if __name__ == "__main__":
    input_file = 'input.txt'  # Nome do arquivo de entrada
    output_file = 'output.txt'  # Nome do arquivo de saída
    process_file(input_file, output_file)
