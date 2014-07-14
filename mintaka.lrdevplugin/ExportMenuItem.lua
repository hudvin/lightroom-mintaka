local LrTasks = import 'LrTasks'
local LrDialogs = import 'LrDialogs'
local lrApplication = import 'LrApplication'
local LrExportSession = import 'LrExportSession'
local LrPathUtils = import 'LrPathUtils'
local LrFileUtils = import 'LrFileUtils'

local function getSelection ()
	 local catalog = lrApplication.activeCatalog()
	 if catalog:getTargetPhoto () then
	      return catalog:getTargetPhotos ()
     else
	      return {}
          end
     end

local function getAppTmpPath()
  local appTmp = 'mintaka'
  local globalTmpPath = LrPathUtils.getStandardFilePath('temp')
  appTmpPath =  LrPathUtils.child(globalTmpPath, appTmp)
  return appTmpPath
end  

function endswith(String,End)
   return End=='' or string.sub(String,-string.len(End))==End
end



local function prepareTmpFolder()
  appTmpPath =  getAppTmpPath()
  local exists = LrFileUtils.exists(appTmpPath)
  if exists then
     for filePath in LrFileUtils.directoryEntries(appTmpPath) do
         if endswith(filePath,'.jpg') then
             LrFileUtils.delete(filePath)           
         end 
     end 
  end  
  LrFileUtils.createDirectory(appTmpPath) 
end

local function performExport()
  prepareTmpFolder() 
	LrTasks.startAsyncTask(function()
	  local catalog = lrApplication.activeCatalog()
	  local photos = getSelection()
	  
	  if next(photos) == nil then
	     LrDialogs.message("Please, select some photos!")
	     return {}
      end
	  
	  local exportSettings = {
                        LR_format = "JPEG",
                        LR_export_colorSpace = "sRGB",
                        LR_export_useSubfolder = false,
                        LR_jpeg_quality = 100,
                        LR_size_resolution = 72,
                        LR_size_resolutionUnits = "inch",
                        LR_outputSharpeningOn = false,
                        LR_export_destinationType = "specificFolder",
                        LR_export_destinationPathPrefix = getAppTmpPath(),
                        LR_collisionHandling = "skip",
						LR_extensionCase = "lowercase",
						LR_jpeg_useLimitSize = false,  
                        LR_size_doConstrain = true,  
                        LR_size_maxHeight = 300,  
                        LR_size_maxWidth = 300,  
                        LR_size_units = "pixels",  
                        LR_size_resizeType = "wh",  
						LR_tokens = {{image_originalName_number_suffix}},
      }

      local params =  {
                        photosToExport = photos,
                        exportSettings = exportSettings
                       }
      local ex = LrExportSession(params)
      
	    ex:doExportOnCurrentTask()

      local csv_items = {}
      for i, rendition in ex:renditions() do
        local status, other = rendition:waitForRender()
        local uuid = rendition.photo:getRawMetadata( 'uuid')
        local filename = LrPathUtils.leafName(other)
        csv_items[uuid] = filename
      end
	    
      local listPath = LrPathUtils.child(getAppTmpPath(), "list.txt")
      local f = io.open(listPath , "w" )
      
      for k, v in pairs(csv_items) do
         local line = k .."," .. v .. '\n'
         f:write(line)
      end
      io.close(f)
	   
	end
	)
end

performExport()


