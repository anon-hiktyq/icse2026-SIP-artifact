import os


def clean_json_content(json_content):
    # Remove newline characters
    cleaned_content = json_content.replace('\n', '')

    # Remove Markdown code block markers
    cleaned_content = cleaned_content.replace('"```json', '')
    cleaned_content = cleaned_content.replace('```"', '')

    cleaned_content = cleaned_content.replace('\\n', '')

    cleaned_content = cleaned_content.replace('\\"', '"')



    return cleaned_content


def process_json_files(directory):
    for filename in os.listdir(directory):
        if filename.endswith('.json'):
            file_path = os.path.join(directory, filename)

            # Read the original content
            with open(file_path, 'r', encoding='utf-8') as file:
                content = file.read()

            # Clean the content
            cleaned_content = clean_json_content(content)

            print(cleaned_content)

            # Write the cleaned content back to the file
            with open(file_path, 'w', encoding='utf-8') as file:
                file.write(cleaned_content)

            print(f"Processed and cleaned: {filename}")


# Replace 'your_directory_path' with the path to the directory containing your JSON files
process_json_files('output-without2/gpt-4o-2024-08-06')
