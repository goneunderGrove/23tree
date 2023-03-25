
#    ______   ______   ____    ____  _______ .______        _______  _______ .__   __.  __   __    __       _______.
#   /      | /  __  \  \   \  /   / |   ____||   _  \      /  _____||   ____||  \ |  | |  | |  |  |  |     /       |
#  |  ,----'|  |  |  |  \   \/   /  |  |__   |  |_)  |    |  |  __  |  |__   |   \|  | |  | |  |  |  |    |   (----`
#  |  |     |  |  |  |   \      /   |   __|  |      /     |  | |_ | |   __|  |  . `  | |  | |  |  |  |     \   \
#  |  `----.|  `--'  |    \    /    |  |____ |  |\  \----.|  |__| | |  |____ |  |\   | |  | |  `--'  | .----)   |
#   \______| \______/      \__/     |_______|| _| `._____| \______| |_______||__| \__| |__|  \______/  |_______/
#

## About
This Python code reads data from an Excel workbook and uses it to fill in placeholders in a Word document to create a cover letter. It then saves the resulting cover letter and a general resume in a directory named after the company being applied to. The code starts by defining file paths for the main directory, the template, and the workbook. It then loads the files and defines the placeholders to be filled in the Word document. The code then iterates through each sheet in the workbook and fills in the values for each column in the sheet. Finally, it saves the resulting cover letter and general resume in a directory named after the company being applied to.

## Install Requiments
In the terminal type the following command 
>``pip install -r requirements.txt``

# Update file
Navigate to the file in the terminal and type ``pwd``
> Open ``Automate_doc_file.py``
Use the output to update line 10 
> ``main_path = r"[*insert output from pwd*]"``

Lastly type ``python3 Automate_doc_file.py``

## Upcoming Version
> The upcoming version of the project will include a web scraper that can extract more details from the job posting just by using the URL. Currently, the scraper works for LinkedIn and uses the Chat-GPT API to interact and create a word cloud, summarize the posting, and identify the most important skills in the posting. This feature will significantly improve the speed and make the end product more dynamic for each job posting.
## Contact

> Discord: Gospel001
