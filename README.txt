cocos2dx版本: 4.0

1、编译工程
   1) windows:
		需安装cmake(3.0+) vs2017+
	
		1、 protobuf(3.9.0)库编译（下载地址:https://github.com/protocolbuffers/protobuf/releases/download/v3.9.0/protobuf-all-3.9.0.zip）:
	   在工程同级目录下解压protobuffer
	   cd protobuf-3.9.0/cmake
	   mkdir win32
	   cd win32
	   cmake .. -A win32
	   打开工程protobuf.sln, 编译
	   
		2、生成cocos vs工程
	   mkdir build
	   cd build
	   cmake .. -A win32
	   
	   