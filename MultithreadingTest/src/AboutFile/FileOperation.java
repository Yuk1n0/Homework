package AboutFile;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;

public class FileOperation {

	public static void SaveToFile(String filename,Object obj) {
		try {
			ObjectOutputStream out = new ObjectOutputStream(
					new FileOutputStream(filename + ".txt"));
			out.writeObject(obj);
			out.close();
		} catch (FileNotFoundException e) {
			System.out.println("未找到文件名！");
			e.printStackTrace();
		} catch (IOException e) {
			System.out.println("写入文件失败！");
			e.printStackTrace();
		}
	}

	public static void copy(File file, File toFile) throws FileNotFoundException,IOException {
		byte[] b = new byte[1024];
		int a;
		FileInputStream fis;
		FileOutputStream fos;
		if (file.isDirectory()) {
			String filepath = file.getAbsolutePath();
			filepath=filepath.replaceAll("\\\\", "/");
			String toFilepath = toFile.getAbsolutePath();
			toFilepath=toFilepath.replaceAll("\\\\", "/");
			int lastIndexOf = filepath.lastIndexOf("/");
			toFilepath = toFilepath + filepath.substring(lastIndexOf ,filepath.length());
			File copy=new File(toFilepath);
			if (!copy.exists()) {
				copy.mkdir();
			}
			for (File f : file.listFiles()) {
				copy(f, copy);
			}
		} 
		else {
			if (toFile.isDirectory()) {
				String filepath = file.getAbsolutePath();
				filepath=filepath.replaceAll("\\\\", "/");
				String toFilepath = toFile.getAbsolutePath();
				toFilepath=toFilepath.replaceAll("\\\\", "/");

				int lastIndexOf = filepath.lastIndexOf("/");
				toFilepath = toFilepath + filepath.substring(lastIndexOf ,filepath.length());

				File newFile = new File(toFilepath);
				fis = new FileInputStream(file);
				fos = new FileOutputStream(newFile);	
				while ((a = fis.read(b)) != -1) {
					fos.write(b, 0, a);
				}
				fis.close();
				fos.close();
			} 
			else {
				fis = new FileInputStream(file);
				fos = new FileOutputStream(toFile);
				while ((a = fis.read(b)) != -1) {
					fos.write(b, 0, a);
				}
				fis.close();
				fos.close();
			}
		}
	}
}
