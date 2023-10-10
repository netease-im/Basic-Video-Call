using System;
using System.IO;
using UnrealBuildTool;
using System.Collections.Generic;
using System.Linq;

public class Nertc : ModuleRules
{
	public Nertc(ReadOnlyTargetRules Target) : base(Target)
	{
        Console.WriteLine("#### Engine Version : " + Target.Version.MajorVersion + "." + Target.Version.MinorVersion);
        Console.WriteLine("#### Target : " + Target.Platform);
		Type = ModuleType.External;
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			LoadWindowsLibrary(Path.Combine(ModuleDirectory, "Win", "x64", "Release"));
		}
		else if (Target.Platform == UnrealTargetPlatform.Win32)
		{
			//LoadWindowsLibrary(Path.Combine(ModuleDirectory, "Win", "Release", "x86"));
		}
		else if (Target.Platform == UnrealTargetPlatform.Android)
		{
			LoadAndroidLibrary(Path.Combine(ModuleDirectory, "Android", "Release"));
		}
		else if (Target.Platform == UnrealTargetPlatform.IOS)
		{
            LoadIOSLibrary(Path.Combine(ModuleDirectory, "IOS", "Release"));
        }
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
            LoadMacLibrary(Path.Combine(ModuleDirectory, "MAc", "Release"));
        }
	}
	public void LoadMacLibrary(string librarypath)
    {
        string[] dirstr = Directory.GetDirectories(librarypath);
        for (int i = 0; i < dirstr.Length; i++)
        {
            string frameworkName = Path.GetFileName(dirstr[i]);
            if (frameworkName.Contains(".framework"))
            {
                PublicFrameworks.Add(Path.Combine(librarypath, frameworkName));
            }
            Console.WriteLine("PublicFrameworks Add " + frameworkName);
        }
    }

    public void LoadIOSLibrary(string librarypath)
    {
        var fileNames = GetAllFileNames(librarypath);
        for (int i = 0; i < fileNames.Count; i++)
        {
            Console.WriteLine("#### i: " + fileNames[i]); 
            string filename = fileNames[i];
			string extension = Path.GetExtension(filename);
            if (extension == ".zip")
            {
                string filenamWithoutExtension = Path.GetFileNameWithoutExtension(filename);
                string filenamWithoutFrameWork = Path.GetFileNameWithoutExtension(filenamWithoutExtension);
                PublicAdditionalFrameworks.Add(new Framework(filenamWithoutFrameWork, Path.Combine(librarypath, filename), ""));
            }
            Console.WriteLine("PublicAdditionalFrameworks Add " + filename);
        }

        string pluginPath = Path.Combine(ModuleDirectory,Target.RelativeEnginePath);
        Console.WriteLine("pluginPath:" + pluginPath);
        Console.WriteLine("librarypath:" + librarypath);
        AdditionalPropertiesForReceipt.Add("IOSPlugin", Path.Combine(librarypath, "APL_IOS.xml"));
        PublicFrameworks.AddRange(new string[] { "CoreML", "VideoToolbox", "Accelerate", "CFNetwork", "OpenGLES", "CoreTelephony" });
    }

    private string soFormatStr = "		<copyFile src=\"$S(PluginDir)/$S(Architecture)/{0}\" dst=\"$S(BuildDir)/libs/$S(Architecture)/{0}\"/>";
    public void LoadAndroidLibrary(string librarypath)
    {
        string xmlTemplateData = File.ReadAllText(Path.Combine(librarypath, "APL_armv7Template.xml"));
        string[] Architectures = { "armeabi-v7a", "arm64-v8a" };
        string sopathwrite = "";
        for (int i = 0; i < Architectures.Length; i++)
        {
            string architecturespath = Path.Combine(librarypath, Architectures[i]);
            List<string> fileNames = GetAllFileNames(architecturespath);
            for (int j = 0; j < fileNames.Count; j++)
            {
                string filename = fileNames[j];
                string extension = Path.GetExtension(filename);
                if (extension == ".so")
                {
                    string sopath = string.Format(soFormatStr, filename);
                    if(!sopathwrite.Contains(sopath))
                    {
                        sopathwrite += sopath + "\r\n";
                    }
                    PublicAdditionalLibraries.Add(Path.Combine(architecturespath, filename));
                    Console.WriteLine("PublicAdditionalLibraries " + filename);
                }
            }
        }
        sopathwrite += "		<copyFile src=\"$S(PluginDir)/nertc-sdk.jar\" dst=\"$S(BuildDir)/libs/nertc-sdk.jar\" />" + "\r\n";
        xmlTemplateData = xmlTemplateData.Replace("<!-- NertcInsert -->", sopathwrite);
        File.WriteAllText(Path.Combine(librarypath, "APL_armv7.xml"), xmlTemplateData);
        AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(librarypath, "APL_armv7.xml"));
    }
	public void LoadWindowsLibrary(string librarypath)
	{
        List<string> fileNames = GetAllFileNames(librarypath);
		for (int i = 0; i < fileNames.Count; i++)
		{
			string filename = fileNames[i];

			string extension = Path.GetExtension(filename);
			if (extension == ".lib")
			{
				PublicAdditionalLibraries.Add(Path.Combine(librarypath, filename));
				Console.WriteLine("AdditionalLibraries Add" + filename);
			}
			else if (extension == ".dll")
			{
				PublicDelayLoadDLLs.Add(Path.Combine(librarypath, filename));
				Console.WriteLine("DelayLoadDLL Add" + filename);
			}

			RuntimeDependencies.Add(Path.Combine("$(ProjectDir)/Binaries/", Target.Platform + "", filename), Path.Combine(librarypath, filename));

			Console.WriteLine("RuntimeDependencies Add" + filename);
		}
	}

	List<string> GetAllFileNames(string path, string pattern = "*")
	{
		List<FileInfo> folder = new DirectoryInfo(path).GetFiles(pattern).ToList();

		return folder.Select(x => x.Name).ToList();
	}
}
