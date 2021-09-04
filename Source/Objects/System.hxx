/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * Objects/System.hxx: File containing methods for JS related to the system.
 *
 * Methods available to interact with the system from Javascript
 *
 * For related information - https://github.com/rodiihernandezz/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

static void SystemExecute(const FunctionCallbackInfo<Value>& Arguments);
static void SystemPlatform(const FunctionCallbackInfo<Value>& Arguments);
static void SystemArguments(const FunctionCallbackInfo<Value>& Arguments);
static void SystemCurrentWorkignDirectory(const FunctionCallbackInfo<Value>& Arguments);
static inline void SystemExitFailure(const FunctionCallbackInfo<Value>& Arguments);
static inline void SystemExitSuccess(const FunctionCallbackInfo<Value>& Arguments);
static inline void SystemCommandOutput(const FunctionCallbackInfo<Value>& Arguments);
static inline void SystemSourceCodeLocation(const FunctionCallbackInfo<Value>& Arguments);

static inline void SystemSourceCodeLocation(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    Arguments.GetReturnValue().Set(
        String::NewFromUtf8(
            Arguments.GetIsolate(),
            ZendaSourceCodeLocation().c_str(),
            NewStringType::kNormal
        ).ToLocalChecked()
    );
}

static void SystemCommandOutput(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(!Arguments[0]->IsUndefined()){
        String::Utf8Value Command(Arguments.GetIsolate(), Arguments[0]);
        Arguments.GetReturnValue().Set(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                GetStdoutFromCommand(string(ToCString(Command))).c_str(),
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    }else
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "You need enter a command for get their output.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
}

static void SystemExecute(const FunctionCallbackInfo<Value>& Arguments){
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "You need to enter one or more commands to the Execute method so that you can execute them in the operating system.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        unsigned short int Iterator = 0;
        for(Iterator; Iterator < Arguments.Length(); Iterator++){
            HandleScope Scope(Arguments.GetIsolate());
            String::Utf8Value Command(Arguments.GetIsolate(), Arguments[Iterator]);
            const char* CharCommand = ToCString(Command);
            system(CharCommand);
        }
    }
}

static void SystemPlatform(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    string OS = OperativeSystem();
    Arguments.GetReturnValue().Set(
        String::NewFromUtf8(
            Arguments.GetIsolate(),
            OS.c_str(),
            NewStringType::kNormal,
            static_cast<int>(OS.length())
        ).ToLocalChecked()
    );
}

static void SystemArguments(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    Local<Context> ArgumentsContext = Context::New(ZendaIsolate);
    Local<Array> ArgumentList = Array::New(ZendaIsolate, CallArguments.size());
    unsigned short int Iterator = 0;
    for(Iterator; Iterator < CallArguments.size(); Iterator++){
        Local<String> SomeArgument = String::NewFromUtf8(ZendaIsolate, CallArguments.at(Iterator).c_str()).ToLocalChecked();
        Maybe<bool> ArgumentAdded = ArgumentList->Set(ArgumentsContext, Iterator, SomeArgument);
    }
    Arguments.GetReturnValue().Set(
        ArgumentList
    );
}

static void SystemCurrentWorkignDirectory(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    Arguments.GetReturnValue().Set(
        String::NewFromUtf8(
            Arguments.GetIsolate(),
            WorkingDirectory.c_str(),
            NewStringType::kNormal,
            static_cast<int>(WorkingDirectory.length())
        ).ToLocalChecked()
    );
}

static inline void SystemExitFailure(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    ExitFailure();
}

static inline void SystemExitSuccess(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    ExitSucces();
}