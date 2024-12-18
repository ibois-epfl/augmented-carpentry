import requests

def list_zenodo_entries(zenodo_record_id):
    url = f'https://zenodo.org/api/records/{zenodo_record_id}'
    response = requests.get(url)
    if response.status_code == 200:
        data = response.json()
        print('## Available Toolheads\n')
        for file in data.get('files', []):
            filename = file['key']
            download_link = file['links']['self']
            print(f'- [{filename}]({download_link})')
    else:
        print('Error fetching data from Zenodo')

if __name__ == '__main__':
    zenodo_record_id = '12578820'  # Replace with your Zenodo record ID
    list_zenodo_entries(zenodo_record_id)