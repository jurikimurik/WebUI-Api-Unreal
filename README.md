# WebUI API Plugin for Unreal Engine
Created as an AI project for the Polish Japanese Academy of Information Technology by Yurii Makovskyi.

That plugin creates communication between the Unreal Engine game and Text Generation WebUI using OpenAI API extension.

Highly inspired by [this project](https://github.com/KellanM/OpenAI-Api-Unreal).

## Installation
### WebUI Setup
1. Download and install [Oobabooga’s Text Generation WebUI](https://github.com/oobabooga/text-generation-webui).
2. Download and prepare at least 1 AI model that supports text generation.
Models compatible with "Transformers" recommended.

![image](https://github.com/user-attachments/assets/ce080e0f-fe33-4116-8155-61bda3f63a48)

3. Check if it generates everything in WebUI without any problems.

![image](https://github.com/user-attachments/assets/f01f9fb7-a411-4747-9317-e78e48d35238)

### Plugin

1. Download the plugin from here.
3. Create a Plugins folder under your project folder.
4. Copy the plugin there. You should have then similar folder structure as : YourProject/Plugins/WebUIAPI.
5. Rebuild the module, if necessary.

### Unreal Engine Project

1. Clone or download template project here (UE 5.4).
2. Extract it and launch “AiOogaboogaProject.uproject”.  
There will be a warning that some modules was not found.  
Just press “Yes” to rebuild the project.  
3. After building, project should launch and you will be ready to go!


## Introduction Video
There is a [video on Youtube](https://youtu.be/hSPzyfICNzI) also.


## Blueprint Functions

Table of Contents
- [Web UI Completion](#web-ui-completion)
- [Web UI Chat Completion](#web-ui-chat-completion)
- [Web UI Stop Generation](#web-ui-stop-generation)
- [Web UI Get Models](#web-ui-get-models)
- [Web UI Load Model](#web-ui-load-model)
- [Web UI Unload Model](#web-ui-unload-model)

### Web UI Completion
This function makes an HTTP request to WebUI for basic completion.
If succeed: Returns true in “Success”, empty “Error Message” and filled “Completion” structure.
If failed:  Returns false in “Success”, text in “Error Message” and empty “Completion”.

![image](https://github.com/user-attachments/assets/96186f16-b7ba-4b08-a69d-2a62f5c320e3)

### Web UI Chat Completion
Make an HTTP request to WebUI for a chat completion.
If succeed: Returns true in “Success”, empty “Error Message” and filled array of “Message” structure.
If failed:  Returns false in “Success”, text in “Error Message” and empty “Messages”.

![image](https://github.com/user-attachments/assets/d05fa46e-50aa-4c13-99c4-70cbbf1cfd75)

### Web UI Stop Generation
Make an HTTP request to WebUI to prevent further generation.	
If succeed: Returns true in “Success”, empty “Error Message” and text in “Message”.
If failed:  Returns false in “Success”, text in “Error Message” and empty “Message”.

![image](https://github.com/user-attachments/assets/2ed22745-0e35-48fe-9637-e890a18a6c16)

### Web UI Get Models
Make an HTTP request to WebUI for retrieving all models that can be loaded.
If succeed: Returns true in “Success”, empty “Error Message” and array of texts in “Message”.
If failed:  Returns false in “Success”, text in “Error Message” and empty “Message”.

![image](https://github.com/user-attachments/assets/4a0bb746-00ab-4f83-9e83-7200d7306a9f)

### Web UI Load Model
Supported: Transformers Only
Make an HTTP request to WebUI to load desired model.
If succeed: Returns true in “Success”, empty “Error Message” and text in “Message”.
If failed:  Returns false in “Success”, text in “Error Message” and empty “Message”.

![image](https://github.com/user-attachments/assets/ec6f625d-2cd2-404b-ac1c-14711c536e9d)

### Web UI Unload Model
Make an HTTP request to WebUI for unloading AI model.
If succeed: Returns true in “Success”, empty “Error Message” and text in “Message”.
If failed:  Returns false in “Success”, text in “Error Message” and empty “Message”.

![image](https://github.com/user-attachments/assets/9fad6452-32f4-4cda-b113-fc9dc986fc45)

## Main Types
In every type, every parameter can be enabled or disabled. 
If enabled, it will be included into JSON request.
If disabled, it won’t be included.
Every parameter is well-commented accordingly to [Oobabooga’s Text Generations WebUI Wiki](https://github.com/oobabooga/text-generation-webui/wiki/03-%E2%80%90-Parameters-Tab).

![image](https://github.com/user-attachments/assets/0dbf4a67-abfd-467b-bcb3-495f230b6ce5)

### Completion Generation Settings
Generation parameters for basic completion. (Retrieved from FastAPI on http://127.0.0.1:5000/docs#/)

![image](https://github.com/user-attachments/assets/95901306-b353-4e14-be6a-b2d6062d6a9a)

### Chat Completion Generation Settings
Generation parameters for chat completions. (Retrieved from FastAPI on http://127.0.0.1:5000/docs#/)

![image](https://github.com/user-attachments/assets/23e054dd-24c6-4c3f-b8fb-86a7b7d91d17)

### Transformer Settings
Setting for transformer type of AI models. (Retrieved from: https://github.com/oobabooga/text-generation-webui/wiki/04-%E2%80%90-Model-Tab)

![image](https://github.com/user-attachments/assets/b9deb00d-7164-4257-80d6-a0628609aba2)



