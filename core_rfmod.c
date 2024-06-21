/* this file from the git repo ww/soruce or something like that.i
 * yes, the original is called core.c
 * it will take 1st argument image: can be a png, yes
 * and output a small "thumbnail" version to the second arg
 * actually thumbnail is a a hardcoded size 106x80 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <magick/MagickCore.h>

int main(int argc,char **argv)
{


  if(argc != 3) {
      fprintf(stdout,"Usage: %s image thumbnail\n",argv[0]);
      exit(0);
    }

  /* Initialize the image info structure and read an image.  */
  MagickCoreGenesis(*argv, MagickTrue); // appears to read our args, but in fact we'll need to strcpy them in
  ExceptionInfo *exception = AcquireExceptionInfo();

  ImageInfo *image_info;
  image_info=CloneImageInfo((ImageInfo *) NULL);

  strcpy(image_info->filename,argv[1]); // we set the filenames memeber of our ImageInfo struct
  Image *images=ReadImage(image_info, exception);

  if (exception->severity != UndefinedException)
    CatchException(exception);
  if (images == (Image *) NULL)
    exit(1);

  /* Convert the image to a thumbnail.  */
  Image *thumbnails=NewImageList();
  Image *tmpimage, *oneimageresized;
  while ((tmpimage=RemoveFirstImageFromList(&images)) != (Image *) NULL) {
      printf("nrows (aka. height):%zu ncols (aka. width:%zu:n", tmpimage->rows, tmpimage->columns); 
    oneimageresized=ResizeImage(tmpimage,106,80,LanczosFilter,1.0,exception);
    if (oneimageresized == (Image *) NULL)
      MagickError(exception->severity,exception->reason,exception->description);
    AppendImageToList(&thumbnails,oneimageresized);
    DestroyImage(tmpimage);
  }

  /* Write the image thumbnail.  */
  strcpy(thumbnails->filename,argv[2]);
  WriteImage(image_info,thumbnails);

  /* Destroy the image thumbnail and exit. */
  thumbnails=DestroyImageList(thumbnails);
  image_info=DestroyImageInfo(image_info);
  exception=DestroyExceptionInfo(exception);
  MagickCoreTerminus();

  return(0);
}
