import requests
import re

def list_zenodo_entries(zenodo_record_id):
    url = f'https://zenodo.org/api/records/{zenodo_record_id}'
    response = requests.get(url)
    if response.status_code == 200:
        data = response.json()
        
        mount_kits = {}

        for file in data.get('files', []):
            filename = file['key']
            filename = filename.split('.')[0]
            download_link = file['links']['self']
            file_size = file['size'] / (1024 * 1024)
            
            filename_lower = filename.lower()
            name_pool = re.split('[_]', filename_lower)

            mount_type = name_pool[0]
            mount_brand = name_pool[1]
            mount_model = name_pool[2]
            try:
                mount_part = name_pool[3]
            except:
                mount_part = "a"

            for key in name_pool:
                if 'drill' in name_pool:
                    mount_type = ":material-screw-machine-flat-top:`drill`"
                elif 'chainsaw' in name_pool:
                    mount_type = ":material-hand-saw:`chain saw`"
                elif 'circularsaw' in name_pool:
                    mount_type = ":material-saw-blade:`circular saw`"
                elif 'sabersaw' in name_pool:
                    mount_type = ":material-hand-saw:`saber saw`"
                elif 'mitersaw' in name_pool:
                    mount_type = ":material-circular-saw:`miter saw`"

            # Group parts by model name
            if mount_model not in mount_kits:
                mount_kits[mount_model] = []
            mount_kits[mount_model].append({
                'filename': filename,
                'type': mount_type,
                'brand': mount_brand,
                'part': mount_part,
                'size': file_size,
                'download_link': download_link
            })
    else:
        print('!!! bug \n\tError fetching data from Zenodo')

    for mount_model, parts in mount_kits.items():
        mount_kits[mount_model] = sorted(parts, key=lambda x: x['part'])

    brands = []
    for mount_model, parts in mount_kits.items():
        for part in parts:
            if part['brand'] not in brands:
                brands.append(part['brand'])
    brands.sort()

    print('| Model name | Mount parts | Brand | type | size (MB) | Download |')
    print('|------------|-------------|-------|------|-----------|----------|')
    for brand in brands:
        for mount_model, parts in mount_kits.items():
            for part in parts:
                if part['brand'] == brand:
                    filename = part['filename']
                    mount_type = part['type']
                    mount_brand = part['brand']
                    mount_part = part['part']
                    file_size = part['size']
                    download_link = part['download_link']
                    print(f'| {mount_model} | {mount_part} | {mount_brand} | {mount_type} | {file_size:.2f} | [:octicons-download-24:]({download_link}) |')

if __name__ == '__main__':
    zenodo_record_id = '14531724'
    list_zenodo_entries(zenodo_record_id)