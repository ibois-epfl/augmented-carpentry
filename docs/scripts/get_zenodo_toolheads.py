import requests
import re

def list_zenodo_entries(zenodo_record_id):
    url = f'https://zenodo.org/api/records/{zenodo_record_id}'
    response = requests.get(url)
    if response.status_code == 200:
        data = response.json()
        
        print('| Filename | type | size (MB) | Download |')
        print('|----------|------|-----------|----------|')

        for file in data.get('files', []):
            filename = file['key']
            filename = filename.split('.')[0]
            download_link = file['links']['self']
            file_size = file['size'] / (1024 * 1024)  # Convert size to MB
            
            # Detect type of object
            obj_type = "test"
            type_pool = re.split('[-_]', filename)
            type_drill_keys = ['drill', 'mesh', 'bit']
            type_saw_keys = ['saw', 'blade']
            type_saw_chain_keys = ['chain', 'plateau']
            type_saw_circular_keys = ['circular']
            type_saw_saber_keys = ['saber']

            for key in type_drill_keys:
                if key in type_pool:
                    obj_type = 'drill'
                    break
            for key in type_saw_keys:
                if key in type_pool:
                    if 'chain' in type_pool:
                        obj_type = 'chain saw'
                    elif 'circular' in type_pool:
                        obj_type = 'circular saw'
                    elif 'saber' in type_pool:
                        obj_type = 'saber saw'
                    else:
                        obj_type = 'saw'
                    break
            
            print(f"| {filename} | `{obj_type}` | {file_size:.2f} | [:octicons-download-24:]({download_link}) |")
    else:
        print('!!! bug \n\tError fetching data from Zenodo')

if __name__ == '__main__':
    zenodo_record_id = '12578820'
    list_zenodo_entries(zenodo_record_id)