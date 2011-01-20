<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2007 Bharat Mediratta
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA  02110-1301, USA.
 */


class RestAuthSiteAdminController extends GalleryController {
	function handleRequest( $form ) {
		$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
		if ($ret) {
			return array($ret, null);
		}

		$error = $status = array();
		if ( isset( $form['action']['save'] ) )  {
			// todo: check sanity of settings


			//end:
			list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'restauth');
			if ($ret) {
				return array($ret, null);
			}

			$settings = array( 'restAuthServer', 'restAuthUser',
				'restAuthPassword', 'restAuthRegister', 
				'restAuthRegistration', 'restAuthRequireGroup' );
			foreach( $settings as $key ) {
				if ( isset( $form[$key] ) ) {
					$ret = $module->setParameter( $key, $form[$key] );
					if ( $ret ) {
						return array( $ret, null );
					}
				} else {
					$ret = $module->removeParameter( $key, $form[$key] );
					if ( $ret ) {
						return array( $ret, null );
					}
				}
			}

			$ret = GalleryCoreApi::unregisterFactoryImplementationsByModuleId('restauth');
			if ($ret) {
				return array($ret, null);
			}

			$ret = $module->performFactoryRegistrations();
			if ($ret) {
				return array($ret, null);
			}


			$status['saved'] = true;
		}

		return array( null, array( 
			'redirect' => array(
				'view' => 'core.SiteAdmin',
				'subView' => 'restauth.RestAuthSiteAdmin' ),
			'error' => $error,
			'status' => $status )
		);
	}
}

class RestAuthSiteAdminView extends GalleryView {
	/**
	 * @see GalleryView::loadTemplate
	 */
	function loadTemplate(&$template, &$form) {
		$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
		if ($ret) {
			return array($ret, null);
		}

		list ($ret, $params) = GalleryCoreApi::fetchAllPluginParameters('module', 'restauth');
		if ($ret) {
			return array($ret, null);
		}

		$RestAuthSiteAdmin = array();

#		list ($ret, $RestAuthSiteAdmin['code']) = HttpAuthHelper::checkConfiguration();
#		if ($ret) {
#			return array($ret, null);
#		}

		/* Load our default values if we didn't just come from this form */
		if ($form['formName'] != 'RestAuthSiteAdmin') {
			$form['formName'] = 'RestAuthSiteAdmin';

			$settings = array( 'restAuthServer', 'restAuthUser',
				'restAuthPassword', 'restAuthRegister',
				'restAuthRegistration', 'restAuthRequireGroup' );
			foreach( $settings as $key ) {
				if (!empty($params[$key])) {
					$form[$key] = $params[$key];
				}
			}
		}

		/* Render HTML body */
		$template->setVariable('RestAuthSiteAdmin', $RestAuthSiteAdmin);
		$template->setVariable('controller', 'restauth.RestAuthSiteAdmin');
		$template->javascript('lib/javascript/BlockToggle.js');

		return array(null, array('body' => 'modules/restauth/templates/RestAuthSiteAdmin.tpl'));
	}
}

?>
